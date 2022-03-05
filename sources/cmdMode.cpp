/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:23:40 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/05 16:10:15 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::_sendGetMode(User& user, Channel *channel)
{
	sendCommand(user, RPLCODE_CHANNELMODEIS, RPL_CHANNELMODEIS(channel->getName(), channel->getModes(), channel->getPass()));
}

void	Command::_channel_i(std::stringstream& completeCommand, User& user, Channel *channel, bool value)
{
	if (value == !channel->getModeI())
	{
		channel->setModeI(value);
		channel->sendToChannel(":" + user.getNickHost() + " " + completeCommand.str() + "\r\n", *this, 0);
	}
	else
		_sendGetMode(user, channel);
}

void	Command::_channel_k(std::stringstream& completeCommand, User& user, Channel *channel, bool value)
{
	std::string pass;

	completeCommand >> pass;
	if (value == !channel->getModeK())
	{
		channel->setModeK(value);
		value ? channel->setPass(pass) : channel->clearPass();
		if (value)
			channel->sendToChannel(":" + user.getNick() + " MODE +k " + channel->getPass() + "\r\n", *this, 0);
		else
			channel->sendToChannel(":" + user.getNick() + " MODE -k " + channel->getPass() + "\r\n", *this, 0);
	}
	else
		_sendGetMode(user, channel);
}

void	Command::_mode(std::stringstream& completeCommand, User& user) {

	std::string	target;
	std::string	modes;
	Channel *channel;

	completeCommand >> target;
	completeCommand >> modes;

	if (target[0] == '#')
	{
		channel = user.getChannel(target);
		if (channel)
		{
			if (modes[0] == '+' || modes[0] == 'i' || modes[0] == 'k')
			{
				for (size_t i = 0; modes[i] ; i++)
				{
					if (modes[i] == 'i')
						_channel_i(completeCommand, user, channel, true);
					if (modes[i] == 'k')
						_channel_k(completeCommand, user, channel, true);
				}
			}
			else if (modes[0] == '-')
			{
				for (size_t i = 0; modes[i] ; i++)
				{
					if (modes[i] == 'i')
						_channel_i(completeCommand, user, channel, false);
					if (modes[i] == 'k')
						_channel_k(completeCommand, user, channel, false);
				}
			}
			if (modes.empty())
				_sendGetMode(user, channel);
		}
	}
	else
	{
		if (target == user.getNick())
		{
			user.setMode((*modes.c_str() == '-' ? false : true), modes.c_str());
			sendCommand(user, RPLCODE_UMODEIS, RPL_UMODEIS(user.getModes()));
		}
	}
}
