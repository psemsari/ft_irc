/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdInvite.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:12:58 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/05 17:02:41 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_invite(std::stringstream& completeCommand, User& user){

	User *userToInvite;
	Channel *channelToJoin;
	std::string target;
	std::string channel;

	completeCommand >> target;
	completeCommand >> channel;

	if (target.empty() || channel.empty())
	{
		sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(_type));
		return ;
	}
	channelToJoin = user.getChannel(channel);
	userToInvite = user.getServer().getUser(target);
	if (!userToInvite)
	{
		sendCommand(user, ERRCODE_NOSUCHNICK, ERR_NOSUCHNICK(target));
		return ;
	}
	else if (!channelToJoin)
	{
		sendCommand(user, ERRCODE_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL(channel));
		return ;
	}
	else if (!channelToJoin->inChannel(user))
	{
		sendCommand(user, ERRCODE_NOTONCHANNEL, ERR_NOTONCHANNEL(channel));
		return ;
	}
	sendCommand(user, RPLCODE_INVITING, RPL_INVITING(target, channel));
	if (!channelToJoin->inList(*userToInvite))
		channelToJoin->addToInvite(userToInvite);
	sendDirect(*userToInvite, PONG, ":" + user.getNick() + " " + completeCommand.str() + "\r\n");
}
