/*
 * accountCommands.cpp
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

#include "Datatypes.h"

#include "Interpreter.h"
#include "AccountCommands.h"

#include "Player.h"

// {{{ > chat [text]

ChatCommand::ChatCommand(PlayerList *pl):Command("chat", pl) {}

ChatCommand::~ChatCommand() {}

void ChatCommand::execute(Player *player, String arguments) {
	for(Player *cur = _playerList->getPlayersHead(); cur != 0; cur = cur->getNext()) {
		if(cur != player)
			cur->sendToPlayer(arguments+"\n");
	}
	player->sendToPlayer("You: "+arguments+"\n");
}

// }}}
// {{{ > dance 

DanceCommand::DanceCommand(PlayerList *pl):Command("dance", pl){}

DanceCommand::~DanceCommand() {}

void DanceCommand::execute(Player *player, String arguments) {
	player->sendToPlayer("You dance around for a while. You feel happy.\n");
}

// }}}
// {{{ > quit

QuitCommand::QuitCommand(PlayerList *pl):Command("quit", pl) {}

QuitCommand::~QuitCommand(){}

void QuitCommand::execute(Player *player, String arguments) {
	player->sendToPlayer("Goodbye!");
	_playerList->destroy(player);
}

// }}}
// {{{ > shutdown

ShutdownCommand::ShutdownCommand(PlayerList *pl):Command("shutdown", pl) {}

ShutdownCommand::~ShutdownCommand() {}

void ShutdownCommand::execute(Player *player, String arguments) {
	player->sendToPlayer("Shutting down...\n");
	_playerList->shutdown(true);
}

// }}}
// {{{ > menu

MenuCommand::MenuCommand(PlayerList *pl):Command("menu", pl) {}

MenuCommand::~MenuCommand() {}

void MenuCommand::execute(Player *player, String arguments) {
	String menu = "Account Menu\n\n"
				 "1) chat\n"
				 "2) dance\n"
				 "3) quit\n"
				 "4) shutdown\n"
				 "5) menu\n";

	player->sendToPlayer(menu);
}

// }}}
// {{{ Interpreter

AccountInterpreter::AccountInterpreter(PlayerList *pl) {
	initialize(pl);
	initializeCommandList();
}

AccountInterpreter::~AccountInterpreter() {
	cleanUp();
}

void AccountInterpreter::initializeCommandList() {
	numberOfCommands = 5;
	commandList = new Command *[numberOfCommands];
	commandList[0] = new ChatCommand(playerList);
	commandList[1] = new DanceCommand(playerList);
	commandList[2] = new QuitCommand(playerList);
	commandList[3] = new ShutdownCommand(playerList);
	commandList[4] = new MenuCommand(playerList);

}

// }}}
