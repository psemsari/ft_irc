/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:58 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/15 18:57:27 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_ping(std::stringstream& completeCommand, User& user) {

	std::string servName = static_cast<std::string>(SERV_NAME);

	(void)completeCommand;
	sendCommand(user, PONG, PONG_MSG(servName));
}
