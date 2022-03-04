/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdKill.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:48:34 by bemoreau          #+#    #+#             */
/*   Updated: 2022/03/02 12:48:34 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_kill(std::stringstream& completeCommand, User& user)
{
    std::string cmd = "KILL";
    std::string nick;
    std::string message;
    User target;
    std::string buf;

    completeCommand >> nick;

	completeCommand >> buf;
	while (buf.empty() == false)
	{
		message += buf;
		message += ' ';
		buf.clear();
		completeCommand >> buf;	
	}
    if (user.getMode('o') == false)
    {
        sendCommand(user, ERRCODE_NOPRIVILEGES, ERR_NOPRIVILEGES());
        return ;
    }
    if (nick.empty() == true || message.empty())
    {
        sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(cmd));
        return ;
    }
    if (nick == SERV_NAME)
    {
        sendCommand(user, ERRCODE_CANTKILLSERVER, ERR_CANTKILLSERVER());
        return ;
    }
    std::map<int, User> tmp = user.getServer().getUsers();
    std::map<int, User>::iterator it = tmp.begin();
    std::map<int, User>::iterator ite = tmp.end();
    while (it != ite)
    {
        if (it->second.getNick() == nick)
	            target = it->second;
        it++;
    }
    if (target.getNick() == DEFAULT_NICKNAME)
    {
        sendCommand(user, ERRCODE_NOSUCHNICK, ERR_NOSUCHNICK(nick));
        return ;
    }
    sendDirect(target, PONG, ":"+ user.getNick() +" NOTICE " + target.getNick() + " You have been killed because: " + message + "\r\n");
	user.getServer().setUnavalaibleName(nick);
    if (target.getNick() == user.getNick())
        user.setIsEnded(true);
    else
        target.getServer().endConnection(target.getFd());
}
