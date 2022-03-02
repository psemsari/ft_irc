/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdTopic.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:13:28 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/25 12:47:42 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_topic(std::stringstream& completeCommand, User& user){

	std::string target;
	std::string topic;
	completeCommand >> target;
	completeCommand >> topic;
	std::cout << "OUTPUT target = " << target << std::endl;
	//User *user_ptr = user.getServer().getUser(target);
	if (target.empty())
		sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(std::string("TOPIC")));
	else if (user.getChannel(target) == NULL)
		sendCommand(user, ERRCODE_NOTONCHANNEL, ERR_NOTONCHANNEL(target));
	else if (user.getChannel(target) && topic.empty())
	{
		sendCommand(user, PONG, completeCommand.str() + "\r\n");
		user.getChannel(target)->sendToChannel(completeCommand.str() + "\r\n", *this, user.getFd());
	}
	else if (user.getChannel(target)->getTopic().empty())
		sendCommand(user, RPLCODE_NOTOPIC, RPL_NOTOPIC(target));
	else
		sendCommand(user, RPLCODE_TOPIC, RPL_TOPIC(target, user.getChannel(target)->getTopic()));
}
