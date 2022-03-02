/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdInvite.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:12:58 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/23 15:53:38 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_invite(std::stringstream& completeCommand, User& user){

	User *userToInvite;
	std::string target;
	std::string channel;

	completeCommand >> target;
	completeCommand >> channel;

	if (target.empty() || channel.empty())
		sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(_type));
	sendCommand(user, RPLCODE_INVITING, RPL_INVITING(channel, target));
	userToInvite = user.getServer().getUser(target);
	user.getChannel(channel)->addToChannel(userToInvite);
	sendDirect(*userToInvite, PONG, ":" + user.getNick() + " " + completeCommand.str());
}
