/***********************************************************************************
 * File: entranceCommands.cpp
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

#include "Datatypes.h"

#include "Interpreter.h"
#include "EntranceCommands.h"
#include "CreationStates.h"

#include "Player.h"


/********************************************************************************
 * START LoginCommand
 ********************************************************************************/

LoginCommand::LoginCommand(PlayerList *pl):Command("login", pl) {}
LoginCommand::~LoginCommand() {}

/**
 * Command to login to a Character or Account.  Check accounts
 * first, then characters.
 *
 * Usage:
 * 		login <character name | account name>
 *
 * Example:
 * 		login dbingham
 */
void LoginCommand::execute(Player *player, String arguments) {



}

/********************************************************************************
 * END LoginCommand / START CreateCommand
 ********************************************************************************/

CreateCommand::CreateCommand(PlayerList *pl):Command("create", pl) {}
CreateCommand::~CreateCommand() {}

/**
 * Command to start the account creation process.  Lead the player through creating
 * their first Account and Character.
 *
 * Usage:
 * 		create <account name>
 *
 * Example:
 * 		create dbingham
 */
void CreateCommand::execute(Player *player, String arguments) {
	Account *account = getPlayerList()->getModelFactory()->getAccountFactory()->create();
	account->setName(arguments);
	player->setAccount(account);
	player->setInterpreter(new CreationStates(getPlayerList()));
}

/********************************************************************************
 * END CreateCommand / START HelpCommand
 ********************************************************************************/

HelpCommand::HelpCommand(PlayerList *pl):Command("help", pl) {}
HelpCommand::~HelpCommand() {}

/**
 * Command to get a list of commands available at the welcome screen
 * plus further explanation of the commands available.
 *
 * Usage:
 * 		help - to list available commands
 * 		help <command name> - to get help on a specific command
 *
 * Example:
 * 		help
 * 		help login
 *
 */
void HelpCommand::execute(Player *player, String arguments) {
	if(arguments.length() == 0) {
		String output = "To enter the game, you first need to specify a character or account to log into.\n"
						"If you don't have one, you'll need to create one.  The command available are as\n"
						"follows: \n"
						"login <character | account> -- Login to a character or account with that name\n"
						"create <account> -- Create an account with the given name\n"
						"help -- Show this menu\n";
		player->sendToPlayer(output);
	} else {
		if(arguments == "login") {

		} else if(arguments == "create") {

		} else {

		}
	}

}

/********************************************************************************
 * END HelpCommand
 ********************************************************************************/
/********************************************************************************
 * START EntranceInterpreter
 ********************************************************************************/

EntranceInterpreter::EntranceInterpreter(PlayerList *pl) {
	initialize(pl);
	initializeCommandList();
}

EntranceInterpreter::~EntranceInterpreter() {
	cleanUp();
}

void EntranceInterpreter::initializeCommandList() {
	numberOfCommands = 3;
	commandList = new Command *[numberOfCommands];
	commandList[0] = new LoginCommand(playerList);
	commandList[1] = new CreateCommand(playerList);
	commandList[2] = new HelpCommand(playerList);
}






