/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:23:40 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/17 19:26:18 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_mode(std::stringstream& completeCommand, User& user) {

	std::string	target;
	std::string	modes;

	completeCommand >> target;
	completeCommand >> modes;
	//	if (!user.isInChannel())
	//		checkTarget(target);
	//	else
	// 		modes = target;
	user.setMode((*modes.c_str() == '-' ? false : true), modes.c_str());
	sendCommand(user, RPLCODE_UMODEIS, RPL_UMODEIS(user.getModes()));
}
