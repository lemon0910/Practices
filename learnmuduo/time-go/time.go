package main

import (
		"encoding/binary"
		"log"
		"net"
		"time"
)

func PanicOnError(err error){
	if err != nil{
		panic(err)
	}
}

func ListenTcpOrDie(listenAddr string) net.Listener{
	listener, err := net.Listen("tcp", listenAddr)
	PanicOnError(err)
	return listener
}

type TimeServer struct {
	listener net.Listener
}

func NewTimeServer(listenAddr string) *TimeServer{
	server := new(TimeServer)
	server.listener = ListenTcpOrDie(listenAddr)
	return server
}

func (s *TimeServer) Serve(){
	defer s.listener.Close()
	for{
		conn, err := s.listener.Accept()
		if err == nil{
			var now int32 = int32(time.Now().Unix())
			binary.Write(conn, binary.BigEndian, &now)
			conn.Close()
		} else {
			log.Println("time:", err.Error())

		}
	}
}

func main(){
	timeServer := NewTimeServer(":2037")
	timeServer.Serve()
}