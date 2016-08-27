package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"net"
	"os"
	"strconv"
	"sync"
	"time"

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

type client struct {
	conn *net.TCPConn
}

func (cli *client) Connect(address string) {
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

	cli.conn = conn
}

var mutex sync.Mutex
var msgnum int64

func main() {
	if len(os.Args) < 3 {
		fmt.Println("please input address and client number")
		return
	}
	address := os.Args[1]
	num, _ := strconv.Atoi(os.Args[2])
	var wg sync.WaitGroup

	for i := 0; i < num; i++ {
		var cli client
		cli.Connect(address)
		wg.Add(1)
		go work(cli.conn, &wg)
	}

	ticker := time.Tick(time.Second)
	for {
		select {
		case <-ticker:
			mutex.Lock()
			//defer mutex.Unlock()
			//fmt.Println(msgnum)
			msgnum = 0
			mutex.Unlock()
		}
	}
	wg.Wait()
}

func work(conn *net.TCPConn, wg *sync.WaitGroup) {
	defer wg.Done()
	for {
		entries := make([]*lemon.LogEntry, 0)
		command := &lemon.WriteCommand{Key: "lemon", Value: "wonder"}
		entry, _ := lemon.NewLogEntry(1, 2, command)
		entries = append(entries, entry)
		req := lemon.NewAppendEntriesRequest(1, 1, 1, 1, "leader", entries)
		var buf bytes.Buffer
		req.Encode(&buf)
		len := buf.Len()
		conn.Write(IntToBytes(int32(len)))
		conn.Write(buf.Bytes())
		fmt.Println("send data to leader")

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
				var resp lemon.AppendEntriesResponse
				data = result.Bytes()
				buffer := bytes.NewBuffer(data)
				resp.Decode(buffer)
				fmt.Println("get data from leader")
				break
			}
		}

		mutex.Lock()
		//defer mutex.Unlock()
		msgnum++
		mutex.Unlock()
	}
}
