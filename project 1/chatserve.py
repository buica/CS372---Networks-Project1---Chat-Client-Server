########################################################################
#   Calvin Bui
#   CS 372 Intro to Networks
#   Project 1 Assignment - Simple client/server chat system
#   chatserver.py - Server program 
#   Last modified: May 5, 2019  
########################################################################
from socket import * # import socket library
import sys

# check for correct amount of arguments and correct usage
if len(sys.argv) != 2:
    print "USAGE: python chatserver.py PORT"
    exit()

# Citation: Lecture 15 Slide for Python TCPServer 
serverPort = int(sys.argv[1]) # take the second argument as port number
serverSocket = socket(AF_INET, SOCK_STREAM) # create TCP socket for server
serverSocket.bind(('', serverPort)) # bind the socket to local address and port
serverSocket.listen(1) # listen for an incoming connection (1 active at a time)
print "The server is ready to receive client's message"

while 1:   #server runs continuously until we manually close it
    # Wait for connection request then accept it
    connectionSocket, addr = serverSocket.accept()
    #clientHandle = connectionSocket.recv(10) # receive client handle first
    
    while 1: # Chat forever until someone quits or closes out
        # receive and print message from client
        recvMessage = connectionSocket.recv(501) # Receive chat message from client (Using 501 just to be safe)
        print "Host B>{}".format(recvMessage) # print message, with client handle preceeding the message

        # send message back to client
        sendMessage = raw_input('Host A>') # get input, making sure handle preceeds message
       
        if sendMessage == '\quit': # allow users to quit
            print "Quitting"
            exit()
        connectionSocket.send(sendMessage) # Send our message to socket
    
    connectionSocket.close()
