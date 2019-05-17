/*******************************************************************
 * Calvin Bui
 * CS 372 Intro to Networks
 * Project 1 Assignment - Simple client/server chat system
 * chatclient.c program
 * Last Modified: May 5, 2019 
 * ****************************************************************/

// Citation: Bulk of code borrowed from client.c example code in 
// OSU's CS 344: Operating Systems I course with instructor Benjamin Brewster
// I previously took this course in Winter term and am retaking it again this term
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int main(int argc, char *argv[])
{
    // Define all our variables and structs
    int socketFD, portNumber, charsWritten, charsRead, handleWritten;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
    char handleBuffer[10]; // User handle, 10 chars max
	char buffer[501]; // max number of bytes we can get at once (501 to account for null terminator)
    
    // error checking for the correct number of arguments (should be 3 total)
    if (argc != 3) 
    { 
        fprintf(stderr,"USAGE: %s HOSTNAME PORT\n", argv[0]);
        exit(0); 
    }

    // Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[2]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Designate IPv4 address family
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname(argv[1]); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL)  // error checking for host
    { 
        fprintf(stderr, "CLIENT: ERROR, no such host\n"); 
        exit(0); 
    }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
	{	
        printf("CLIENT: ERROR connecting");
        exit(0);
    }
    // Ask client to enter handle name
    printf("Enter your one-word handle (10 characters max): ");
    fgets(handleBuffer, sizeof(handleBuffer) - 1, stdin);
    handleBuffer[strcspn(handleBuffer, "\n")] = '\0'; // Remove the trailing \n that fgets adds
    
    // Get input message from user while chat runs continuously
    while (1)
    {
        printf("%s>", handleBuffer);
        memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
        fgets(buffer, sizeof(buffer) - 1, stdin); // Get input from the user, trunc to buffer - 1 chars, leaving \0
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove the trailing \n that fgets adds
        
        if (strcmp(buffer,"\\quit") == 0) // Let client quit by typing in '\quit' at any time 
        {    
            printf("Quitting\n");
            exit(0);
        }

        // Send message to server
        charsWritten = send(socketFD, buffer, strlen(buffer), 0); // Write to the server
        
        if (charsWritten < 0) // error checking when sending
        {
            printf("CLIENT: ERROR writing to socket");
            exit(0);
        }
        // Get return message from server
        memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
        charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read data from the socket, leaving \0 at end
        if (charsRead < 0) 
        {
            printf("CLIENT: ERROR reading from socket");
            exit(0);
        }
        printf("Host A>%s\n", buffer);  // Print message received from server
    }
	close(socketFD); // Close the socket
    printf("Server has disconnected");
	return 0;
}