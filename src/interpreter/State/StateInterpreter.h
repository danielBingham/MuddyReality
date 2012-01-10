/***********************************************************************************
 * File: StateInterpreter.h
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
 ***********************************************************************************/

#ifndef STATEINTERPRETER_H_
#define STATEINTERPRETER_H_

#include "Interpreter.h"
#include "Player.h"

class State {
	public:
		State();
		State(PlayerList *playerList);
		~State();

		virtual void introduction(Player *player) = 0;
		virtual bool isCompleted(Player *player, String input) = 0;

	protected:
		PlayerList *getPlayerList();

	private:
		PlayerList *_playerList;
};

class StateInterpreter: public Interpreter {
	public:
		StateInterpreter();
		StateInterpreter(PlayerList *playerList);
		~StateInterpreter();

		void interpret(Player *player, String command);

	protected:
		PlayerList *getPlayerList();

		State *getCurrentState();
		bool nextState();

		void initialize();
		virtual void initializeStateList() = 0;

		void welcome(Player *player);
		void cleanUp();

	private:
		PlayerList *_playerList;

		int _currentState;
		State **_stateList;
		int _numberOfStates;


};

#endif /* STATEINTERPRETER_H_ */
