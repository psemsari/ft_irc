/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:35:31 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/28 13:14:29 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_part(std::stringstream& completeCommand, User& user)
{
	std::list<std::string> toPart;
	std::stringstream stream;
	std::string word, str;
	Channel *channeltofind;

	completeCommand >> str;
	stream.str(str);
	while (!stream.eof()) {
		std::getline(stream, word, ',');
		toPart.push_back(word);
	}

	while (!toPart.empty())
	{
		channeltofind = user.getChannel(toPart.front());
		if (channeltofind == NULL)
		{
			if (user.getServer().getChannel(toPart.front()) == NULL)
				sendCommand(user, ERRCODE_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL(toPart.front()));
			else
				sendCommand(user, ERRCODE_NOTONCHANNEL, ERR_NOTONCHANNEL(toPart.front()));
		}
		else
		{
			user.removeChannel(toPart.front());
			channeltofind->removeFromChannel(&user);
			if (channeltofind->getList().empty())
			{
				sendCommand(user, PONG, ":" + user.getNick() + " PART " + toPart.front() + "\r\n");
				user.getServer().eraseChannel(toPart.front()); //segfault avec part et 2 clients
			}
			else
			{
				channeltofind->sendToChannel(":" + user.getNick() + " PART " + toPart.front() + "\r\n", *this, user.getFd());
				sendCommand(user, PONG, ":" + user.getNick() + " PART " + toPart.front() + "\r\n");
			}
		}
		toPart.pop_front();
	}
}
