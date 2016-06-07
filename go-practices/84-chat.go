package main

import (
	"io"
	"log"
	"net"
)

type connection struct {
	conn net.Conn
	send chan []byte
}

type ChatServer struct {
	listener   net.Listener
	conns      map[*connection]bool
	boardcast  chan []byte
	register   chan *connection
	unregister chan *connection
}

func NewChatServer(listenAddr string) *ChatServer {
	var chatserver ChatServer
	chatserver.listener, _ = net.Listen("tcp", listenAddr)
	chatserver.conns = make(map[*connection]bool)
	chatserver.boardcast = make(chan []byte)
	chatserver.register = make(chan *connection)
	chatserver.unregister = make(chan *connection)

	return &chatserver
}

func (c *connection) input(boardcast chan []byte) {
	for {
		message, err := c.readMessage()
		if err != nil {
			log.Println(err)
			break
		}

		boardcast <- message
	}
}

func (c *connection) output() {
	defer c.close()
	for m := range c.send {
		_, err := c.conn.Write(m)
		if err != nil {
			log.Println(err)
			break
		}
	}
}

func (c *connection) close() {
	log.Println("close connection")
	c.conn.Close()
}

func (c *connection) readMessage() (message []byte, err error) {
	message = make([]byte, 1024)
	_, err = io.ReadAtLeast(c.conn, message, 1)
	if err != nil {
		return nil, err
	}

	return message, nil
}

func (s *ChatServer) ServerConn(conn net.Conn) {
	c := &connection{conn: conn, send: make(chan []byte, 1024)}
	s.register <- c
	defer func() { s.unregister <- c }()

	go c.output()
	c.input(s.boardcast)
}

func ServerTcp(l net.Listener, server *ChatServer, name string) {
	defer l.Close()
	for {
		conn, _ := l.Accept()
		go server.ServerConn(conn)
	}
}

func (s *ChatServer) Run() {
	go ServerTcp(s.listener, s, "chat")
	for {
		select {
		case c := <-s.register:
			s.conns[c] = true
			log.Println("connection up")
		case c := <-s.unregister:
			delete(s.conns, c)
			close(c.send)
			log.Println("connection down")
		case m := <-s.boardcast:
			for c := range s.conns {
				c.send <- m
			}
		}
	}
}

func main() {
	log.SetFlags(log.LstdFlags | log.Lmicroseconds | log.Lshortfile)
	server := NewChatServer(":8899")
	server.Run()
}
