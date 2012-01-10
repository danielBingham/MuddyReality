/*
 * Player.h
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

#ifndef PLAYER_H_
#define PLAYER_H_

#include <queue>
#include <list>

#include "Datatypes.h"
#include "ModelFactory.h"
#include "Account.h"
#include "Character.h"

class Interpreter;
class Socket;

class Player {
		friend class Socket;
		friend class ServerSocket;
		friend class PlayerList;

	public:
		Player();
		Player(Socket *s);
		~Player();

		// Handle the head of input queue, execute whatever command and append
		// the output to the output queue.
		void handleInput();

		// Set the command interpreter.
		void setInterpreter(Interpreter *ci);

		// Send output to the player.
		void sendToPlayer(String out, ...);

		// Allow non-friends to walk the player list.
		Player *getNext();
		Player *getPrev();

		// This player's account and character accessors.
		Account *getAccount();
		void setAccount(Account *account);

		Character *getCharacter();
		void setCharacter(Character *character);

	protected:

		// Determine whether or not this Player has output waiting
		// to be processed.
		bool hasOutput();

		// Determine whether or not this Player has input waiting
		// to be processed.
		bool hasInput();

		// Add the String out to the tail of the out queue (outQ).
		void output(String out);

		// Add the String in to the tail of the in queue (inQ).
		void input(String in);

		// Return the next output string from the output queue.
		String nextOutput();

		// Return the next input in the queue to be processed.
		String nextInput();

		// This player is quitting and has been marked for destruction.
		bool destroy;

		Socket *socket;

		Interpreter *commandInterpreter;

		Player *next;
		Player *prev;

		std::queue<String> inQ;
		std::queue<String> outQ;

	private:
		/**
		 * Send a prompt to this player.
		 */
		void sendPrompt();


		/**
		 * Initialize this player.
		 */
		void initialize();

		bool atPrompt;

		Account *_account;
		Character *_character;


};

class PlayerList {
	public:
		PlayerList();
		PlayerList(ModelFactory *mf);
		~PlayerList();

		/**
		 * Set whether or not to shutdown the game.
		 * This will be moved else where eventually, but
		 * for the moment it is here.
		 */
		void shutdown(bool execute);

		/**
		 * Do we need to shutdown the game?
		 */
		bool shutdown();

		/**
		 * Destroy a player and kick them out of the game.  This may be the result of a quit.
		 */
		void destroy(Player *p);

		/**
		 * Add the specified Player to the player list.  Adds to the head of the list.
		 */
		void add(Player *p);

		/**
		 * Remove the specified Player from the player list.
		 */
		void remove(Player *p);

		/**
		 * The number of players currently in the game.
		 */
		int getNumberOfPlayers();

		/**
		 * Returns a pointer to the head of the players list.
		 */
		Player *getPlayersHead();

		/**
		 * Returns a pointer to the tail of the players list.
		 */
		Player *getPlayersTail();

		/**
		 * Pushes the Player p passed to it into the back
		 * of the input Queue.
		 */
		void addToInputQueue(Player *p);

		/**
		 * Returns a pointer to the player popped from the
		 * head of the input queue.
		 */
		Player *getFromInputQueue();

		/**
		 * Removes a player from the inputQueue - UGLY
		 */
		void removePlayerFromInputQueue(Player *p);

		/**
		 * Checks to make sure the input queue is not empty.
		 */
		bool arePlayersWithInput();

		ModelFactory *getModelFactory();

	protected:
		Player *playersHead;
		Player *playersTail;

		int numberOfPlayers; // The number of players currently in the game.

		bool shouldShutdown;


		std::queue<Player *> inputQueue;

		ModelFactory *modelFactory;
};

#endif /* PLAYER_H_ */
