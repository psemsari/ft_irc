/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNotice.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:56:08 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/23 11:12:29 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_notice(std::stringstream& completeCommand, User& user){

	std::string target;
	completeCommand >> target;
	std::cout << "OUTPUT target = " << target << std::endl;
	User *user_ptr = user.getServer().getUser(target);
	std::cout << completeCommand.str() << std::endl;
	if (target[0] == '#')
	{
		Channel* chan_ptr = user.getChannel(target);
		if (chan_ptr != NULL)
			chan_ptr->sendToChannel(":" + user.getNick() + " " + completeCommand.str() + "\r\n", *this, user.getFd());
	}
	else
	{
		std::cout << completeCommand.str() << std::endl;
		if (user_ptr != NULL)
			sendDirect(*user_ptr, PONG, ":" + user.getNick() + " " + completeCommand.str() + "\r\n");
	}
}
