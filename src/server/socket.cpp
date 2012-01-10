/***********************************************************************************
 * File: socket.cpp
 * Definition:
 *
 * Contents:
 *
 *
 * Copyright:
 *		Copyright (C) 2009-2011 Daniel Bingham (http://www.theroadgoeson.com)
 *
 * License:
 *
 * This software is licensed under the MIT Open Source License which reads as
 * follows:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information see here: http://www.opensource.org/licenses/mit-license.php
 *
 ***********************************************************************************/
// System libraries we need.
#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <iostream>
#include <string>

// Our headers.
#include "Socket.h"
#include "SocketException.h"
#include "Player.h"

#include "Logger.h"
#include "Datatypes.h"

const static int READ_SIZE = 4096;

/********************************************************************************
 * General Socket related functions.											*
 ********************************************************************************/

// Checks the global errno variable and throws an appropriate exception.
// Only checks socket related errors - but checks all socket related errors.
// Should only be called when there IS an error.  Will throw an exception.
void handleSocketError(String file, int l) {
	char line[128];

	snprintf(line, 128, "%d", l);

	switch (errno) {
		case ENETDOWN:
			throw NetworkIsDownException(file, line);
		case EINPROGRESS:
			throw FunctionStillWorkingException(file, line);
		case EADDRINUSE:
			throw AddressInUseException(file, line);
		case EINVAL:
			throw InvalidSocketException(file, line);
		case EADDRNOTAVAIL:
			throw RemoteAddressInvalidException(file, line);
		case EAFNOSUPPORT:
			throw AddressFamilyNotSupportedException(file, line);
		case ENOBUFS:
			throw NotEnoughMemoryInBuffersException(file, line);
		case ENOTSOCK:
			throw NotRealSocketException(file, line);
		case EWOULDBLOCK:
			throw WouldBlockException(file, line);
		case ECONNREFUSED:
			throw ConnectionRefusedException(file, line);
		case EFAULT:
			throw InvalidParametersException(file, line);
		case EISCONN:
			throw SocketAlreadyConnectedException(file, line);
		case ENETUNREACH:
			throw DestinationAddressUnreachableException(file, line);
		case ETIMEDOUT:
			throw TimeOutException(file, line);
		case EACCES:
			throw AccessDeniedException(file, line);
		case ENETRESET:
			throw NetworkResetException(file, line);
		case ENOTCONN:
			throw SocketNotConnectedException(file, line);
		case EOPNOTSUPP:
			throw UnsupportedOperationException(file, line);
		case ESHUTDOWN:
			throw ShutdownSocketException(file, line);
		case EHOSTUNREACH:
			throw HostUnreachableException(file, line);
		case ECONNABORTED:
			throw ConnectionAbortedException(file, line);
		case ECONNRESET:
			throw ConnectionResetException(file, line);
		case EMFILE:
			throw OutOfSocketDescriptorsException(file, line);
		default:
			throw SocketException(file, line);
	}
}

/********************************************************************************
 * Socket																		*
 ********************************************************************************/

// Initialize this socket.
void Socket::initialize() {
	descriptor = 0;
	player = 0;
}

// Set up the socket, call initialize.
Socket::Socket() {
	initialize();
}

// Call initialize and set the file descriptor.
Socket::Socket(int fd) {
	initialize();
	descriptor = fd;
}

// Close's the socket descriptor wrapped by this
// Socket and throws any exceptions caught forward.
Socket::~Socket() {
	if (close(descriptor) < 0) {
		try {
			handleSocketError(__FILE__, __LINE__);
		}
		catch (...) {
			throw ;
		}
	}
}

// A utility function to strip the newlines off the end of
// a string.
void Socket::stripNewline(char *buf) {
	for (int i = strlen(buf); i > 0 && (buf[i] == '\n' || buf[i] == '\r' || buf[i] == 0); i--) {
		buf[i] = 0;
	}
}

// Read from this socket's descriptor and send the input
// to it's associated player for queueing and parsing.
bool Socket::Read() {
	char buf[READ_SIZE + 1];

	int n = 0;
	if ((n = read(descriptor, buf, READ_SIZE)) < 0) {
		try {
			handleSocketError(__FILE__, __LINE__);
		}
		catch (...) {
			throw ;
		}
		return false;
	}
	else if(n > 0) {
		buf[n] = 0;
		stripNewline(buf);
		player->input(buf);
		return true;
	}
	else {
		return false;
	}
}

// Write the String passed as output to this socket's
// descriptor.
void Socket::Write(String output) {
	char *buf = new char[output.length() + 1];
	strcpy(buf, output.c_str());

	int n = 0;
	while ((n = write(descriptor, buf, output.length() + 1)) > 0 && static_cast<unsigned> (n) < output.length()) {
		if (static_cast<unsigned> (n) < output.length() + 1) {
			output = output.substr(n, (output.length() - n));
			delete[] buf;
			buf = new char[output.length() + 1];
			strcpy(buf, output.c_str());
		}
	}
	if (n < 0) {
		// Find out what the error is and pass it on.
		try {
			handleSocketError(__FILE__, __LINE__);
		}
		catch (...) {
			delete[] buf;
			throw ;
		}
	}
	delete []buf;

}

// Return this socket's descriptor.
int Socket::getDescriptor() {
	return descriptor;
}

/********************************************************************************
 * ServerSocket																	*
 ********************************************************************************/

void ServerSocket::initialize() {
	memset((char *) &socketAddress, 0, sizeof(socketAddress));
	listeningSocket = 0;

	noTime.tv_sec = 0;
	noTime.tv_usec = 0;

	FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	FD_ZERO(&readSet);

	players = 0;

	maxFD = 0;
}

// Initialize the server socket to effectively zero.
ServerSocket::ServerSocket() {
	initialize();
}

// Create a server socket given a playerlist to attach
// it to.
ServerSocket::ServerSocket(PlayerList *pl) {
	initialize();
	players = pl;
}

// Destroy the server socket, destroying it's socket
// address structure and closing the mother socket.
// Throws any exceptions caught forward.
ServerSocket::~ServerSocket() {
	if (close(listeningSocket) < 0) {
		try {
			handleSocketError(__FILE__, __LINE__);
		}
		catch (...) {
			throw ;
		}
	}
}

// Initialize this server socket's address, then bind the socket to that address
// and begin listening for connections.
void ServerSocket::initializeSocket() {
	log->log("Initializing the mother socket.");
	try {
		initializeSocketAddress();
		CreateSocket();
		Bind();
		Listen();
	}
	catch (...) {
		throw ;
	}
}

// Initializes the read, write and error sets to prepare for polling.
void ServerSocket::initializeDescriptorSetsForPolling() {
	FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	FD_ZERO(&errorSet);
	if (players->getNumberOfPlayers() == 0) {
		maxFD = listeningSocket + 1;
	}
	else {
		for (Player *p = players->getPlayersHead(); p != 0; p = p->next) {
			FD_SET(p->socket->descriptor, &readSet);
			FD_SET(p->socket->descriptor, &writeSet);
			FD_SET(p->socket->descriptor, &errorSet);
			if (p->socket->descriptor > maxFD)
				maxFD = p->socket->descriptor;
		}
	}
	FD_SET(listeningSocket, &readSet);
}

// Poll the connected sockets for input, output and error states and
// handle those states.  Throws any Exceptions caught.
void ServerSocket::poll() {
	try {
		if (players->getNumberOfPlayers() < 1) {
			initializeDescriptorSetsForPolling();

			log->log("No players, going to sleep while waiting for a player.");
			// Block in select waiting for new connections.
			if (select(maxFD, &readSet, (fd_set *) 0, (fd_set *) 0, 0) < 0) {
				handleSocketError(__FILE__, __LINE__);
			}
			log->log("New connection, waking up.");
		}

		initializeDescriptorSetsForPolling();

		if ((select(maxFD + 1, &readSet, &writeSet, &errorSet, &noTime)) < 0) {
			handleSocketError(__FILE__, __LINE__);
		}

		// Bring in the new connections.
		AcceptNewConnections();

		// Kick out those with errors.
		Error();

		// Read and handle input from those who have it.
		Read();

		// Write to those who are ready.
		Write();

		// Destroy those who are disconnecting.
		Destroy();

	}
	catch (...) {
		throw ;
	}
}

// Wait for milliseconds # of milliseconds.
void ServerSocket::wait(int microseconds) {
	timeval t;
	t.tv_sec = 0;
	t.tv_usec = microseconds;

	if(select(0, (fd_set *)0, (fd_set *)0, (fd_set *)0, &t) < 0) {
		try {
			handleSocketError(__FILE__, __LINE__);
		}
		catch(...) {
			throw;
		}
	}
}

// Initialize the socket address with the values configured.
void ServerSocket::initializeSocketAddress() {
	log->log("Initializing the socket address to port 4000 and any ip address.");
	memset((char *) &socketAddress, 0, sizeof(socketAddress)); // Clear the address structure.

	socketAddress.sin_family = AF_INET; // Set the family to the internet address family.
	socketAddress.sin_port = htons(4000); // Turn the port into network byte ordering, and set it to 4000.
	socketAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Tell it to bind to any ip address.
}

// Create a valid socket descriptor for the listeningSocket.
// Throws exceptions according to handleSocketError() on error.
void ServerSocket::CreateSocket() {
	log->log("Creating the listening socket.");
	if ((listeningSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		try {
			handleSocketError(__FILE__, __LINE__);
		}
		catch (...) {
			throw ;
		}
	}
}

// Binds the server socket to the address specified in socketAddress.
// Throws exceptions according to handleSocketError() on error.
void ServerSocket::Bind() {
	log->log("Binding the listening socket.");
	if (bind(listeningSocket, (struct sockaddr *) &socketAddress, sizeof(socketAddress)) < 0) {
		try {
			handleSocketError(__FILE__, __LINE__);
		}
		catch (...) {
			throw ;
		}
	}
}


// Starts the server socket listening with a backlog of 16.
// Throws exceptions according to handleSocketError() on error.
void ServerSocket::Listen() {
	log->log("Beginning listening.");
	if (listen(listeningSocket, 16) < 0) {
		try {
			handleSocketError(__FILE__, __LINE__);
		}
		catch (...) {
			throw ;
		}
	}
}


// Attempts to accept any new connections add them to the PlayerList.  Creates
// a new Socket and a new Player for each new connection.
// Throws exceptions on failure according to handleSocketError().
void ServerSocket::Accept() {
	int desc = -1;
	socklen_t socketAddressLength = sizeof(socketAddress);
	if ((desc = accept(listeningSocket, (struct sockaddr *) &socketAddress, &socketAddressLength)) < 0) {
		try {
			handleSocketError(__FILE__, __LINE__);
		}
		catch (...) {
			throw ;
		}
	}

	log->log("A new connection has been accepted.");
	if (desc >= maxFD) {
		maxFD = desc + 1;
	}

	// Create the Socket that wraps this descriptor.  Create the Player
	// that wraps that Socket and add that Player to the PlayerList.
	// Talk about dense code...

	Player *p = new Player(new Socket(desc));
	players->add(p);
}


// Poll the listening descriptor to determine if there are any new connections
// waiting in the connection queue.  If there are, accept them.
// Throws exceptions on failure according to handleSocketError().
void ServerSocket::AcceptNewConnections() {
	if (FD_ISSET(listeningSocket, &readSet)) {
		log->log("Connection attempt begun.  Connection in the read set.");
		try {
			Accept();
		}
		catch (...) {
			throw ;
		}
	}
}


// Poll all descriptors using select to determine which ones are ready for
// reading.  Call those descriptors read functions.  Throw any exceptions
// caught on for later handling.
void ServerSocket::Read() {
	for (Player *cur = players->getPlayersHead(); cur != 0; cur = cur->next) {
		if (FD_ISSET(cur->socket->getDescriptor(), &readSet)) {
			try {
				if(cur->socket->Read())
					players->addToInputQueue(cur);
				else
					cur->destroy = true; // If they were in the read set with no input, something is wrong.
			}
			catch (...) { // If any sort of error occurs, disconnect the player.
				cur->destroy = true;
				throw;
			}
		}
	}

}


// Poll all descriptors using select to determine which ones are ready for
// writing.  Call those descriptor's write functions and pass it the next
// output from the associated players output queue.  Throw any exceptions
// caught for later handling.
void ServerSocket::Write() {
	for (Player *cur = players->getPlayersHead(); cur != 0; cur = cur->next) {
		if (FD_ISSET(cur->socket->getDescriptor(), &writeSet) && cur->hasOutput()) {
			try {
				cur->socket->Write(cur->nextOutput());
			}
			catch (...) {
				cur->destroy = true;
				throw ;
			}
		}
	}
}


// Poll all descriptors using select to determine which ones are in an
// exception or error state.  Destroy those descriptors, closing the
// connection and removing their players from the player list.
void ServerSocket::Error() {

	for (Player *cur = players->getPlayersHead(); cur != 0; cur = cur->next) {
		if (FD_ISSET(cur->socket->getDescriptor(), &errorSet)) {
			try {
				log->log("Losing a player.");
				players->remove(cur);
				delete cur;
			}
			catch (...) {
				throw ;
			}
		}
	}
}

// Run through all the players in the destroy players queue and destroy the player in question.
void ServerSocket::Destroy() {
	Player *next = 0, *cur = 0;
	for (cur = players->getPlayersHead(); cur != 0; cur = next) {
		next = cur->next;
		if (cur->destroy) {
			log->log("Losing a player.");
			players->remove(cur);
			delete cur;
		}
	}
}



