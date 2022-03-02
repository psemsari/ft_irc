/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMotd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:48:27 by bemoreau          #+#    #+#             */
/*   Updated: 2022/03/02 12:48:28 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_motd(std::stringstream& completeCommand, User& user) {

    (void)completeCommand;
    std::string msg = MOTD;
    if (msg.empty() == true)
    {
        sendCommand(user, 422, ERR_NOMOTD());
        return;
    }
    std::string name = static_cast<std::string>(SERV_NAME);
    sendCommand(user, 375, RPL_MOTDSTART(name));
    sendCommand(user, 372, RPL_MOTD(msg));
    sendCommand(user, 376, RPL_ENDOFMOTD());
}
