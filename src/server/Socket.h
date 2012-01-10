/*
 * socket.h
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
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <netinet/in.h>

#include "Datatypes.h"

class Player;
class PlayerList;

/**
 * 	Socket
 */
class Socket {
		friend class ServerSocket;
		friend class Player;

	public:
		Socket();
		Socket(int fd);
		~Socket();

	protected:
		/**
		 * Returns the file descriptor this socket wraps.
		 */
		int getDescriptor();



		/**
		 * Read input from this socket's descriptor and send it
		 * to the associated player for queuing and parsing.
		 */
		bool Read();

		/**
		 * Writes output to the associated descriptor and
		 * returns true or false, success or fail.
		 */
		void Write(String output);

		Player *player;

	private:
		void initialize();

		/**
		 * A utility function to strip the newline off the end of an input string.
		 */
		void stripNewline(char *buf);

		void logInputCodes(char *buf);

		int descriptor;

};

/**
 * ServerSocket
 */
class ServerSocket {

	public:
		ServerSocket();
		ServerSocket(PlayerList *pl);
		~ServerSocket();

		/**
		 * 	Initializes this ServerSocket's address structure, binds it
		 * to the address and port assigned to it and sets it to
		 * listening.
		 */
		void initializeSocket();

		/**
		 * Uses select to poll all descriptors in the set and
		 * determines if they are reading for reading and writing.
		 * If they are, it call's the socket's associated read.
		 */
		void poll();

		/**
		 * Wait for the given number of milliseconds.  Uses select to wait.
		 */
		void wait(int microseconds);

	protected:

		/**
		 * Check the mother descriptor for new connections and if they are
		 * found Accept() them.
		 */
		void AcceptNewConnections();

		/**
		 * Accepts any new connections queued on listeningSocket.
		 * Throws Exceptions on error descended from SocketException
		 * according to the package local function handleSocketError() (socket.cpp)
		 */
		void Accept();

		/**
		 * Calls select to poll descriptors and determine
		 * if there are descriptors in the input queue.  Cycle through
		 * the PlayerList (players) to find which Player's sockets
		 * are in the read set, and call those Player's Socket's read()
		 * functions.
		 */
		void Read();

		/**
		 * Uses select to poll the descriptors and determine if there
		 * are descriptors in the ouput queue.  Cycle through the PlayerList
		 * (players) to find which Player's sockets are in the write set
		 * and call those Player's Socket's write() functions.
		 */
		void Write();
		void Error(); // Handles the error set.

		/**
		 * Disconnect and destroy those players who are ready to be disconnected.
		 */
		void Destroy();

	private:

		/**
		 * Prepares the read, write and error sets for polling.
		 */
		void initializeDescriptorSetsForPolling();

		/**
		 * Initialize this server socket.
		 */
		void initialize();

		/**
		 * Initializes the sockaddr_in structure socketAddress with the
		 * values configured for this server.
		 */
		void initializeSocketAddress();

		/**
		 * Call the socket function to create a socket for this server and
		 * store the descriptor in listeningSocket.
		 * Throws Exceptions on error descended from SocketException
		 * according to the package local function handleSocketError(socket.cpp)
		 */
		void CreateSocket();

		/**
		 * Bind's this listening server socket to the address specified in
		 * socketAddress.
		 * Throws Exceptions on error descended from SocketException
		 * according to the package local function handleSocketError (socket.cpp)
		 */
		void Bind();

		/**
		 * Starts this server listening for connections.
		 * Currently set for hard coded backlog of 16.
		 * Throws Exceptions on error descended from SocketException
		 * according to the package local function handleSocketError (socket.cpp)
		 */
		void Listen();

		int listeningSocket;

		sockaddr_in socketAddress;

		timeval noTime;

		fd_set readSet;
		fd_set writeSet;
		fd_set errorSet;

		PlayerList *players;

		int maxFD;
};

#endif /* SOCKET_H_ */
