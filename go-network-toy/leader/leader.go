package main

import (
	"bytes"
	"container/list"
	"encoding/binary"
	"fmt"
	"net"
	"os"
	"sync"

	"../lemon"
)

func IntToBytes(value int32) []byte {
	var buf = make([]byte, 4)
	binary.LittleEndian.PutUint32(buf, uint32(value))
	return buf
}

func BytesToInt32(buf []byte) int32 {
	return int32(binary.LittleEndian.Uint32(buf))
}

type leader struct {
	listener *net.TCPListener
	follower *net.TCPConn
	f        *os.File
	mutex    sync.Mutex
	que      *list.List
}

type msg struct {
	conn *net.TCPConn
	data []byte
	clic chan []byte
}

func NewLeader(listenAddr *net.TCPAddr) *leader {
	var server leader
	server.listener, _ = net.ListenTCP("tcp", listenAddr)

	server.f, _ = os.OpenFile("leader.log", os.O_RDWR|os.O_CREATE, 0600)
	server.que = list.New()

	return &server
}

func (server *leader) Connect(address string) {
	if address == "" {
		fmt.Println("addr is empty")
		return
	}

	tcpaddr, err := net.ResolveTCPAddr("tcp", address)
	if err != nil {
		fmt.Println("add format is wrong")
		return
	}

	conn, err := net.DialTCP("tcp4", nil, tcpaddr)
	if err != nil {
		fmt.Println("DialTCP error")
		return
	}

	server.follower = conn
	go followerwork(server)
}

func (server *leader) ListenTCP() {
	defer server.listener.Close()
	for {
		conn, _ := server.listener.AcceptTCP()
		{
			fmt.Println("client connected")
			go work(conn, server)
		}

	}
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("please input address")
		return
	}
	address := os.Args[1]
	listenaddr, _ := net.ResolveTCPAddr("tcp4", ":8888")
	server := NewLeader(listenaddr)
	server.Connect(address)
	server.ListenTCP()
}

func work(conn *net.TCPConn, server *leader) {
	for {
		data := make([]byte, 1024)
		result := bytes.NewBuffer(nil)
		n := 0
		var lens int32
		for {
			datalen, _ := conn.Read(data[0:])
			result.Write(data[0:datalen])
			n += datalen
			if lens == 0 && n >= 4 {
				lens = BytesToInt32(result.Next(4))
			}
			if (lens != 0) && (n == int(4+lens)) {
				var req lemon.AppendEntriesRequest
				data = result.Bytes()
				buffer := bytes.NewBuffer(data)
				req.Decode(buffer)
				clic := make(chan []byte)
				climsg := msg{
					conn: conn,
					data: data,
					clic: clic,
				}
				server.mutex.Lock()
				server.f.Write(data)
				fmt.Println("get data form client")
				server.que.PushBack(climsg)
				server.mutex.Unlock()
				<-clic
				server.mutex.Lock()
				server.f.Write(data)
				server.mutex.Unlock()
				break
			}
		}

		resp := lemon.NewAppendEntriesResponse(1, true, 1, 1)
		var buf bytes.Buffer
		resp.Encode(&buf)

		len := buf.Len()
		conn.Write(IntToBytes(int32(len)))
		conn.Write(buf.Bytes())
		fmt.Println("send data to client")
	}
}

func followerwork(server *leader) {
	for {
		server.mutex.Lock()
		quelen := server.que.Len()
		server.mutex.Unlock()
		for quelen != 0 {
			quelen--
			server.mutex.Lock()
			temp := server.que.Front().Value
			server.mutex.Unlock()

			var m msg
			m, _ = temp.(msg)

			templen := len(m.data)
			server.follower.Write(IntToBytes(int32(templen)))
			server.follower.Write(m.data)
			fmt.Println("send data to follower")

			n := 0
			var lens int32
			lens = 0
			data := make([]byte, 1024)
			result := bytes.NewBuffer(nil)

			for {
				datalen, _ := server.follower.Read(data[0:])
				result.Write(data[0:datalen])
				n += datalen
				if lens == 0 && n >= 4 {
					lens = BytesToInt32(result.Next(4))
				}
				if (lens != 0) && (n == int(4+lens)) {
					var resp lemon.AppendEntriesResponse
					data = result.Bytes()
					buffer := bytes.NewBuffer(data)
					resp.Decode(buffer)
					fmt.Println("get data form follower")
					m.clic <- data
					server.mutex.Lock()
					server.que.Remove(server.que.Front())
					server.mutex.Unlock()
					break
				}
			}

		}
	}
}
