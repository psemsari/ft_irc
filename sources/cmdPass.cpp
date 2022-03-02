/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:34 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/28 19:33:46 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_pass(std::stringstream& completeCommand, User& user) {

	std::cout << "Pass command :" << completeCommand.str() << std::endl;
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
