/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:34 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/03 15:48:05 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_pass(std::stringstream& completeCommand, User& user) {

	if (!user.getUserOrNickCmd() && !user.getPassGiven())
	{
		std::string pass;
		std::string cmd = "PASS";
		completeCommand >> pass;
		if (pass.empty())
		{
			sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(cmd));
		}
		if (pass != user.getServer().getPassword())
			user.setIsEnded(true);
	}
	else
	{
		sendCommand(user, ERRCODE_ALREADYREGISTRED, ERR_ALREADYREGISTRED());
	}
	user.setPassGiven(true);
}
