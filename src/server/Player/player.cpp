/*
 * player.cpp
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

#include <string>
#include <cstdarg>
#include <cstdio>

#include "Datatypes.h"

#include "Player.h"
#include "Socket.h"

#include "Logger.h"

#include "Interpreter.h"
#include "EntranceCommands.h"

/********************************************************************************
 * Player																		*
 ********************************************************************************/

// Initialize the Player.
void Player::initialize() {
	socket = 0;

	next = 0;
	prev = 0;

	destroy = false;
	atPrompt = false;

	_character = 0;
	_account = 0;
}

// Call initialize.
Player::Player() {
	initialize();
}

// Call initialize then set the Player's socket to s.
Player::Player(Socket *s) {
	initialize();
	s->player = this;
	socket = s;
}

// Call initialize
Player::~Player() {
	delete socket;
	delete commandInterpreter;
	initialize();
}

Player *Player::getNext() {
	return next;
}

Player *Player::getPrev() {
	return prev;
}

// Send the string in 'out' to a player's output queue.
void Player::sendToPlayer(String out, ...) {
	char buffer[4096];
	va_list args;


	va_start(args, out);

	vsnprintf(buffer, 4096, out.c_str(), args);

	va_end(args);

	if(atPrompt)
		output("\r\n");
	output(buffer);
	sendPrompt();
}

// Determine whether or not there is output
// in the output queue waiting to be processed.
bool Player::hasOutput() {
	return !outQ.empty();
}

// Determine whether or not there is input in the input
// queue waiting to be processed.
bool Player::hasInput() {
	return !inQ.empty();
}

// Pop the next input off the front of the input queue.
String Player::nextInput() {
	String s = inQ.front();
	inQ.pop();
	return s;
}

// Push the String out to the tail of the output queue.
void Player::output(String out) {
	outQ.push(out);
}

// Push the String in to the tail of the input queue.
void Player::input(String in) {
	inQ.push(in);
}

// Pop the next output off the front of the output queue.
String Player::nextOutput() {
	String s = outQ.front();
	outQ.pop();
	return s;
}

// Send a prompt to the player.
void Player::sendPrompt() {
	output("\r\n> ");
	atPrompt = true;
}

// Handle this player's input.
void Player::handleInput() {
	commandInterpreter->interpret(this, nextInput());
}

void Player::setInterpreter(Interpreter *ci) {
	commandInterpreter = ci;
}

Account *Player::getAccount() {return _account;}
void Player::setAccount(Account *account) {_account = account;}

Character *Player::getCharacter() {return _character;}
void Player::setCharacter(Character *character) {_character = character;}

/********************************************************************************
 * PlayerList																	*
 ********************************************************************************/

// Initialize the head and tail of the Player list.
PlayerList::PlayerList() {
	playersHead = 0;
	playersTail = 0;
	numberOfPlayers = 0;
	shouldShutdown = false;
	modelFactory = 0;
}

PlayerList::PlayerList(ModelFactory *mf) {
	playersHead = 0;
	playersTail = 0;
	numberOfPlayers = 0;
	shouldShutdown = false;
	modelFactory = mf;
}

// Cycle through the PlayerList and delete all Players on the list.
PlayerList::~PlayerList() {
	for (Player *cur = playersHead, *next = 0; cur != playersTail; cur = next) {
		next = cur->next;
		delete cur;
	}
}

void PlayerList::shutdown(bool execute) {
	shouldShutdown = execute;
}

bool PlayerList::shutdown() {
	return shouldShutdown;
}

void PlayerList::destroy(Player *p) {
	p->destroy = true;
}

// Add the Player p to the tail of the player list.
void PlayerList::add(Player *p) {
	if (playersHead && playersTail) {
		p->prev = playersTail;
		playersTail->next = p;
		playersTail = p;
	}
	else {
		playersHead = playersTail = p;
	}
	String welcomeText = "Welcome to Muddy Reality alpha 6.\n"
				"This is a stand in for a proper welcome text.\n"
				"To join the game, please either login or create\n"
				"an account. To login to an account or character\n"
				"type 'login <character or account name>' at the\n"
				"prompt.  To create a new account, type 'create <account name>'\n"
				"at the prompt.  For additional information, type 'help'.\n";

	p->sendToPlayer(welcomeText);
	// Initialize the player with an account interpreter.
	p->setInterpreter(new EntranceInterpreter(this));
	numberOfPlayers++;
}

// Remove the player from the player list.
void PlayerList::remove(Player *p) {
	if (playersHead != p && playersTail != p) {
		p->prev->next = p->next;
		p->next->prev = p->prev;
		p->prev = 0;
		p->next = 0;
	}
	else if(playersHead == p && playersTail == p) {
		playersHead = 0;
		playersTail = 0;
	}
	else if (playersHead == p) {
		playersHead = playersHead->next;
		playersHead->prev = 0;
		p->next = 0;
		p->prev = 0;
	}
	else if (playersTail == p) {
		playersTail = playersTail->prev;
		playersTail->next = 0;
		p->next = 0;
		p->prev = 0;
	}
	removePlayerFromInputQueue(p);
	numberOfPlayers--;
}

// Get the number of players currently in the game.
int PlayerList::getNumberOfPlayers() {
	return numberOfPlayers;
}

// Return a pointer to the head of the player list.
Player *PlayerList::getPlayersHead() {
	return playersHead;
}

// Return a pointer to the tail of the player list.
Player *PlayerList::getPlayersTail() {
	return playersTail;
}

// Add the Player p to the tail of the input queue. This
// should be called on players who have input that is
// ready to be processed.
void PlayerList::addToInputQueue(Player *p) {
	inputQueue.push(p);
}

// Return a pointer to the player popped off the head
// of the input queue - the next player to have his/her
// input handled.
Player *PlayerList::getFromInputQueue() {
	Player *p = inputQueue.front();
	inputQueue.pop();
	return p;
}

// Cycle through the input queue until we find the player we're looking for,
// add them back onto the queue in the order we pop them off.
// TODO: THIS IS UGLY AS FUCK!
void PlayerList::removePlayerFromInputQueue(Player *p) {
	std::queue<Player *> tmp;

	while(!inputQueue.empty()) {
		if(inputQueue.front() != p)
			tmp.push(inputQueue.front());
		inputQueue.pop();
	}

	while(!tmp.empty()) {
		inputQueue.push(tmp.front());
		tmp.pop();
	}
}

// Are there players with input?
bool PlayerList::arePlayersWithInput() {
	return !inputQueue.empty();
}

ModelFactory *PlayerList::getModelFactory() {
	return modelFactory;
}



