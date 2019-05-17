******************************************************************************
Calvin Bui
CS 372 Introduction to Computer Networks
Programming Assignment #1 README file
Last Modified May 5, 2019
******************************************************************************
For this project, we were to implement a client-server application
using socket programming API. My Project utilizes TCP Protocols.
My Citations are listed below as well as within each program themselves.

My testing machine used is a Windows 10 desktop running multiple instances of
PuTTy in 2 separate windows: one connected to flip1, and the other connected to flip2.
I tested my programs on ports 30444 and 30420 successfully.

COMPILE AND EXECUTE INSTRUCTIONS:
1. Make sure permissions are set by typing "chmod +x chatserve.py" and "chmod +x chatclient.c"
    chatserve.py can be ran on any flip server as long as chatclient.c is on a different one.

2. Execute chatserve first by typing "python chatserve.py PORT" using any port number you wish (30000+ recommended).

3. On a separate flip server, COMPILE chatclient.c next by typing "gcc -o chatclient chatclient.c"

4. Execute chatclient by typing "chatclient SERVER-HOSTNAME PORT" where SERVER-HOSTNAME is the
    full name of the flip server chatserve is running on (i.e. flip1.engr.oregonstate.edu) and 
    PORT is the same port number chosen for chatserve.py to run on.

5. Start by typing handle name on chatclient.c first, followed immediately by the typing first message.
    It's important that the client sends the first message, or else the server will wait forever.

6. Respond with a message on chatserve.py, and repeat 6 and 7 as necessary.

7. Type '\quit' in any window to exit when finished. (or CTRL+C if that doesn't work)

LANGUAGES:
The chat server (chatserve.py) was implemented in Python  and 
the chat client (chatclient.c) was implemented in C.

CITATIONS:
I made heavy use of Beej's Guide to Network Programming for the chatclient.c
file, specifically the 6.2 Simple Stream Client page. 
Source:  http://beej.us/guide/bgnet/html/multi/clientserver.html#simpleserver

I also made use of some past CS 344 Operating Systems 1 example client code from
instructor Benjamin Brewster as a source of reference.

For the chatserve.py programm, I used the examples in the lecture slides as
a reference, and also used Python's official 2.6.5 Standard Library 
Documentation which was suggested by Mr. Redfield. I made use of
the 21.17.4.1. SocketServer.TCPServer Example section.
Source: https://docs.python.org/release/2.6.5/library/socketserver.html#socketserver-tcpserver-example

Another reference I also made use of for this is a geeksforgeeks.com implementation for a 
simple chat server in Python
SOURCE: https://www.geeksforgeeks.org/simple-chat-room-using-python/
