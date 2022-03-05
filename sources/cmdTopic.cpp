/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdTopic.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:13:28 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/05 20:11:48 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_topic(std::stringstream& completeCommand, User& user){

	std::string target;
	std::string topic;
	Channel *channel;

	completeCommand >> target;
	completeCommand >> topic;
	if (target.empty())
	{
		sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(std::string("TOPIC")));
		return ;
	}
	channel = user.getChannel(target);
	if (channel == NULL)
		sendCommand(user, ERRCODE_NOTONCHANNEL, ERR_NOTONCHANNEL(target));
	else if (channel && !topic.empty())
	{
		channel->setTopic(topic);
		sendCommand(user, PONG, completeCommand.str() + "\r\n");
		channel->sendToChannel(":" + user.getNick() + " " + completeCommand.str() + "\r\n", *this, user.getFd());
	}
	else if (channel->getTopic().empty())
		sendCommand(user, RPLCODE_NOTOPIC, RPL_NOTOPIC(target));
	else
		sendCommand(user, RPLCODE_TOPIC, RPL_TOPIC(target, channel->getTopic()));
}
