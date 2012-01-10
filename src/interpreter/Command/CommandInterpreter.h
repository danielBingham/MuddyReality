/***********************************************************************************
 * File: CommandInterpreter.h
 * Definition:
 *
 * Contents:
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
 *
 *					Copyright (C) 2011 Daniel Bingham
 ***********************************************************************************/

#ifndef COMMANDINTERPRETER_H_
#define COMMANDINTERPRETER_H_

#include "Datatypes.h"
#include "Interpreter.h"

class Player;
class PlayerList;

class Command {
		friend class CommandInterpreter;

	public:
		Command();
		Command(String command, PlayerList *pl);
		~Command();

		virtual void execute(Player *player, String arguments) = 0;

		String getCommand();
		PlayerList *getPlayerList();

	protected:
		String _command;
		PlayerList *_playerList;
};

class CommandInterpreter: public Interpreter {
	public:
		CommandInterpreter();
		CommandInterpreter(PlayerList *pl);
		~CommandInterpreter();

		void interpret(Player *player, String command);

	protected:

		/**
		 * Initialize the interpreter.
		 */
		void initialize(PlayerList *pl);

		/**
		 * Clean up after the command interpreter.  Called at
		 * destruction.
		 */
		void cleanUp();

		/**
		 * Trim the whitespace off the front and back of a string.
		 */
		String trim(String command);


		virtual void initializeCommandList() = 0;

		PlayerList *playerList;
		Command **commandList;
		int numberOfCommands;
};

#endif /* COMMANDINTERPRETER_H_ */
