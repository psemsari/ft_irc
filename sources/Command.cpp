/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:44:44 by fdidelot          #+#    #+#             */
/*   Updated: 2021/12/07 19:18:07 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include <iomanip>

/************************************************************/
/*					Constructor/Destructor					*/
/************************************************************/
Command::Command(std::string commandName) :
											_type(commandName) {

	return ;
}

Command::~Command(void) {

	return ;
}

/************************************************************/
/*						Operators							*/
/************************************************************/

/************************************************************/
/*					Members functions						*/
/************************************************************/
void	Command::sendCommand(User& user, int msgId, std::string toSend) const {

	std::stringstream numberStream;
	std::string servName = static_cast<std::string>(SERV_NAME);

	//ADD write rights verification
	if (msgId != PONG)
	{
		numberStream << std::setw(3) << std::setfill('0') << msgId;
		toSend.insert(0, RPL_MESSAGE(servName, numberStream.str(), user.getNick()));
	}
	user.addToSend(toSend);
}

void	Command::sendDirect(User& user, int msgId, std::string toSend) const {

	std::stringstream numberStream;
	std::string servName = static_cast<std::string>(SERV_NAME);

	//ADD write rights verification
	if (msgId != PONG)
	{
		numberStream << std::setw(3) << std::setfill('0') << msgId;
		toSend.insert(0, RPL_MESSAGE(servName, numberStream.str(), user.getNick()));
	}
	user.getServer().sendCommand(user.getFd(), toSend);
}

void	Command::sendStartMsgs(User& user) const {

	std::string servName = static_cast<std::string>(SERV_NAME);
	std::string servCreation = static_cast<std::string>(CREATION_DATE);

	sendCommand(user, RPLCODE_WELCOME, RPL_WELCOME(user.getNick()));
	sendCommand(user, RPLCODE_YOURHOST, RPL_YOURHOST(servName, SERV_VERSION));
	sendCommand(user, RPLCODE_CREATED, RPL_CREATED(servCreation));
	sendCommand(user, RPLCODE_MYINFO, RPL_MYINFO(servName, SERV_VERSION));
}

void	Command::launchCommand(std::stringstream& completeCommand, User& user) {

	void	(Command::*command[NB_COMMAND])(std::stringstream&, User&) = {
		&Command::_pass,
		&Command::_nick,
		&Command::_user,
		&Command::_cap,
		&Command::_mode,
		&Command::_join,
		&Command::_ping,
		&Command::_privmsg,
		&Command::_part,
		&Command::_quit,
		&Command::_oper,
		&Command::_motd,
		&Command::_list,
		&Command::_kill,
		&Command::_kick,
		&Command::_who,
		&Command::_whois,
		&Command::_topic,
		&Command::_invite
	};
	std::string commandId[NB_COMMAND] = {
		"PASS",
		"NICK",
		"USER",
		"CAP",
		"MODE",
		"JOIN",
		"PING",
		"PRIVMSG",
		"PART",
		"QUIT",
		"OPER",
		"motd",
		"LIST",
		"kill",
		"KICK",
		"WHO",
		"WHOIS",
		"TOPIC",
		"INVITE"
	};

	int	i;
	for (i = 0; i < NB_COMMAND; i++)
	{
		if (_type == commandId[i])
		{
			(this->*command[i])(completeCommand, user);
			break;
		}
	}
	if (i == NB_COMMAND)
		send(user.getFd(),	ERR_UNKNOWNCOMMAND(_type).c_str(),
							ERR_UNKNOWNCOMMAND(_type).size(), 0);
}
