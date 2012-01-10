/*
 * Interpreter.cpp
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

#include "Logger.h"
#include "Interpreter.h"
#include "CommandInterpreter.h"

#include "Player.h"

/********************************************************************************
 * START Command
 ********************************************************************************/

// The parent class of all commands.  A wrapper
// for a command string and execute function.
// Cannot be instantiated.
Command::Command() {
	_playerList = 0;
	_command = "";
}
Command::Command(String command, PlayerList *pl) {
	_playerList = pl;
	_command = command;

}
Command::~Command() {}

String Command::getCommand() { return _command; }
PlayerList *Command::getPlayerList() { return _playerList; }


/********************************************************************************
 * END Command / START Interpreter
 ********************************************************************************/
CommandInterpreter::CommandInterpreter() {
	initialize(0);
}

CommandInterpreter::CommandInterpreter(PlayerList *pl) {
	initialize(pl);
}

CommandInterpreter::~CommandInterpreter() {
	cleanUp();
}

void CommandInterpreter::initialize(PlayerList *pl) {
	commandList = 0;
	numberOfCommands = 0;
	playerList = pl;
}

// Clean up after the interpreter.
void CommandInterpreter::cleanUp() {
	for(int i = 0; i < numberOfCommands; i++)
		delete commandList[i];
	delete[] commandList;

}

// Pull all whitespace off the front and back of the command.
String CommandInterpreter::trim(String command) {
	int start = 0, end = 0;

	for (start = 0; start < command.length(); start++)
		if (!isspace(command[start]))
			break;

	for (end = command.length(); end > 0; end--)
		if (!isspace(command[end]))
			break;

	return command.substr(start, end);
}

// Interpret the command string and call the appropriate execute
// function.
void CommandInterpreter::interpret(Player *player, String command) {
	if (commandList == 0)
		return;

	String trimmedCommand = trim(command);

	for (int i = 0; i < numberOfCommands; i++) {
		int length = commandList[i]->getCommand().length();
		if (commandList[i]->getCommand() == trimmedCommand.substr(0, length)) {
			String arguments = "";
			if (command.length() > length)
				arguments = trim(command.substr(length, command.length()));
			commandList[i]->execute(player, arguments);
			player->sendToPlayer("\n");
			return;
		}
	}

	player->sendToPlayer("Argle bargle gloph gliff?\n");
}
