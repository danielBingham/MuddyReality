/*
 * AccountCommands.h
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

#ifndef ACCOUNTCOMMANDS_H_
#define ACCOUNTCOMMANDS_H_

#include "Interpreter.h"
#include "CommandInterpreter.h"

class Player;
class PlayerList;

class ChatCommand: public Command {
	public:
		ChatCommand(PlayerList *pl);
		~ChatCommand();

		void execute(Player *player, String arguments);
};

class DanceCommand: public Command {
	public:
		DanceCommand(PlayerList *pl);
		~DanceCommand();

		void execute(Player *player, String arguments);
};

class QuitCommand: public Command {
	public:
		QuitCommand(PlayerList *pl);
		~QuitCommand();

		void execute(Player *player, String arguments);
};

class ShutdownCommand: public Command {
	public:
		ShutdownCommand(PlayerList *pl);
		~ShutdownCommand();

		void execute(Player *player, String arguments);
};

class MenuCommand: public Command {
	public:
		MenuCommand(PlayerList *pl);
		~MenuCommand();

		void execute(Player *player, String arguments);
};



class AccountInterpreter: public CommandInterpreter {
	public:
		AccountInterpreter(PlayerList *pl);
		~AccountInterpreter();

	protected:
		void initializeCommandList();
};


#endif /* ACCOUNTCOMMANDS_H_ */
