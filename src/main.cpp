/***********************************************************************************
 * File: main.cpp
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
#include <iostream>
#include <ctime>
#include <cstdio>

#include "InterpreterFactory.h"
#include "GameLibrary.h"
#include "Socket.h"
#include "Player.h"
#include "SocketException.h"

#include "Utilities.h"
#include "Logger.h"

InterpreterFactory *interpreterFactory = 0;
PlayerList *playerList = 0;
GameLibrary *gameLibrary = 0;
ServerSocket *server = 0;

void heartbeat(int tics) {

}

int main(int argv, char **argc) {
	String version = "alpha 6";
	time_t seconds = 0;

	time(&seconds);
	printf("Starting up Muddy Reality %s at %s", version.c_str(), ctime(&seconds));

	clock_t hundredthOfASecond = CLOCKS_PER_SEC / 100;

	printf("Initializing the Muddy Reality logger.\n");
	initializeLog();

	log->log("Muddy Reality %s logger started up at %s.", version.c_str(), log->getTime().c_str());

	playerList = new PlayerList();
	gameLibrary = new GameLibrary();
	interpreterFactory = new InterpreterFactory(playerList, gameLibrary);
	server = new ServerSocket(playerList, interpreterFactory);

	try {
		server->initializeSocket();
	}
	catch (SocketException ex) {
		log->log("Socket Exception occurred while trying to boot up the server socket.");
		log->log(ex.message);
		log->log("Shutting down with errors.");
		Exit(1);
	}
	catch (...) {
		log->log("Unknown Exception occurred while trying to boot up the server socket.");
		log->log("Shutting down with errors.");
		Exit(1);
	}

	log->log("Muddy Reality %s successful boot up at %s.", version.c_str(), log->getTime().c_str());


	// This is the number of loops we've executed since we started.
	unsigned long tics = 0;

	while (!playerList->shutdown()) {


		// Mark the start of the loop.
		clock_t startLoop = clock();


		// Poll the server for connections, input and output.
		try {
			server->poll();
		}
		catch (SocketException ex) {
			log->log("A Socket Exception occurred: " + ex.message);
		}
		catch (...) {
			log->log("An unknown exception occurred.");
		}

		// Handle any player input.
		while (playerList->arePlayersWithInput()) {
			playerList->getFromInputQueue()->handleInput();
		}

		// Anything that needs to happen once every so many cycles
		// can happen in here.
		heartbeat(tics);


		// Mark the end of the loop.
		clock_t endLoop = clock();


		// If we've taken less than a 1/10th of a second for this loop
		// wait out the rest of the 1/10th of a second.  If we've taken
		// more than it - then keep going and hope we catch up.
		if (endLoop - startLoop < hundredthOfASecond) {
			server->wait(hundredthOfASecond - (endLoop - startLoop));
		}

		// We've finished a loop, so incrememt the ticker.
		tics++;
		if (tics >= static_cast<unsigned> (-1))
			tics = 0;

	}
	log->log("Shutting down...");

	log->log("Shutting down the server socket.");
	try {
		delete server;
	}
	catch (SocketException ex) {
		log->log("A Socket Exception occurred while attempting to destroy the server: " + ex.message);
	}
	catch (...) {
		log->log("An unknown exception occurred while attempting to destroy the server.");
	}

	log->log("Deleting the InterpreterFactory.");
	delete interpreterFactory;

	log->log("Deleting the model factory.");
	delete modelFactory;

	log->log("Deleting the Player List.");
	delete playerList;

	destroyLog();

	return 0;

}

