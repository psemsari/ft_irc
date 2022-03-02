/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdList.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:45:48 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/18 14:37:09 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_list(std::stringstream& completeCommand, User& user)
{
	Server::Channel_map& map = user.getServer().getChannelMap();
	Server::Channel_map_it it = map.begin();
	Server::Channel_map_it ite = map.end();

	(void)completeCommand;
	for (;it != ite; it++)
	{
		sendCommand(user, RPLCODE_LIST, RPL_LIST(it->first, ""));
	}
	sendCommand(user, RPLCODE_LISTEND, RPL_LISTEND());
}
