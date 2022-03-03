/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdQuit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:47:46 by bemoreau          #+#    #+#             */
/*   Updated: 2022/03/03 18:39:09 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void    Command::_quit(std::stringstream& completeCommand, User& user) {

    std::string arg;
    std::string reply;

    completeCommand >> arg;
    reply = "QUIT " + arg + "\r\n";
	send(user.getFd(), reply.c_str(), reply.size(), SEND_OPT);
    user.setIsEnded(true);
}
