/***********************************************************************************
 * File: stateInterpreter.cpp
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

#include "StateInterpreter.h"

/********************************************************************************
 * START State
 ********************************************************************************/

State::State() {_playerList = 0;}
State::State(PlayerList *playerList) {_playerList = playerList;}
State::~State() {}

PlayerList *State::getPlayerList() { return _playerList; }

/********************************************************************************
 * END State
 ********************************************************************************/
/********************************************************************************
 * BEGIN StateInterpreter
 ********************************************************************************/

void StateInterpreter::initialize() {
	_playerList = 0;
	_stateList = 0;
	_currentState = 0;
	_numberOfStates = 0;
}

StateInterpreter::StateInterpreter() {
	initialize();
}
StateInterpreter::StateInterpreter(PlayerList *playerList) {
	initialize();
	_playerList = playerList;
}
StateInterpreter::~StateInterpreter() {cleanUp();}

void StateInterpreter::interpret(Player *player, String command) {
	if(getCurrentState()->isCompleted(player, command)) {
		if(nextState()) {
			getCurrentState()->introduction(player);
		}
	} else {
		getCurrentState();
	}
}

void StateInterpreter::welcome(Player *player) {
	getCurrentState()->introduction(player);
}

State *StateInterpreter::getCurrentState() {return _stateList[_currentState];}
bool StateInterpreter::nextState() {
	(_currentState < _numberOfStates ? _currentState++ : _currentState=-1);
	return (_currentState == -1 ? false : true);
}

PlayerList *StateInterpreter::getPlayerList() {return _playerList;}

void StateInterpreter::cleanUp() {
	if(_stateList != 0) {
		for(int i = 0; i < _numberOfStates; i++) {
			delete _stateList[i];
		}
		delete [] _stateList;
	}
}


