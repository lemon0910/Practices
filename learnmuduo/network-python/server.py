#!/usr/bin/python

import socket, time

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind(('', 8888))
serversocket.listen(5)

while True:
    (clientsocket, address) = serversocket.accept()
    data = clientsocket.recv(4096)
    datetime = time.asctime() + '\n'
    clientsocket.send('hello ' + data)
    clientsocket.send("My time is " + datetime)
    clientsocket.close()
