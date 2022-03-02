/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNames.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:07:52 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/28 14:37:07 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_names(std::stringstream& completeCommand, User& user)
{

	std::string toSearch;
	std::string ret;
	completeCommand >> toSearch;
	Channel *channel = user.getServer().getChannel(toSearch);

	if (channel == NULL)
		return;
	ret = channel->usersFormat();
	sendCommand(user, RPLCODE_NAMREPLY, RPL_NAMREPLY(toSearch, ret));
	sendCommand(user, RPLCODE_ENDOFNAMES, RPL_ENDOFNAMES());
}
