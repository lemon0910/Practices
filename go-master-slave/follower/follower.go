package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"net"
	"os"

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

type follower struct {
	listener *net.TCPListener
	f        *os.File
}

func NewFollower(listenAddr *net.TCPAddr) *follower {
	var server follower
	server.listener, _ = net.ListenTCP("tcp", listenAddr)
	server.f, _ = os.OpenFile("follower.log", os.O_RDWR|os.O_CREATE, 0600)

	return &server
}

func (server *follower) ListenTCP() {
	defer server.listener.Close()
	for {
		conn, _ := server.listener.AcceptTCP()
		{
			fmt.Println("leader connect")
			go work(conn, server)
		}

	}
}

func main() {
	listenaddr, _ := net.ResolveTCPAddr("tcp4", ":8889")
	server := NewFollower(listenaddr)
	server.ListenTCP()
}

func work(conn *net.TCPConn, server *follower) {
	for {
		data := make([]byte, 1024)
		result := bytes.NewBuffer(nil)
		n := 0
		var lens int32
		for {
			datalen, _ := conn.Read(data[0:])
			n += datalen
			result.Write(data[0:datalen])
			if lens == 0 && n >= 4 {
				lens = BytesToInt32(result.Next(4))
			}
			if (lens != 0) && (n == int(4+lens)) {
				var req lemon.AppendEntriesRequest
				data = result.Bytes()
				buffer := bytes.NewBuffer(data)
				req.Decode(buffer)
				server.f.Write(data)
				fmt.Println("get data from leader")
				break
			}
		}

		resp := lemon.NewAppendEntriesResponse(1, true, 1, 1)
		var buf bytes.Buffer
		resp.Encode(&buf)

		len := buf.Len()
		conn.Write(IntToBytes(int32(len)))
		conn.Write(buf.Bytes())
		fmt.Println("send data to leader")
	}
}
