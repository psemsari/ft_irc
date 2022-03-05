/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdDie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:29:49 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/05 15:29:51 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

extern void *data;

void    deleteUsers(Server *srv, std::map<int, User> users)
{
	std::map<int, User>::iterator it = users.begin();
	std::map<int, User>::iterator ite = users.end();

	while (it != ite)
	{
		srv->endConnection(it->second.getFd());
		it++;
	}
}

void	KillServer(int sigId)
{
	if (sigId == SIGQUIT || sigId == SIGINT)
	{
		Server *tmp;
		tmp = (Server *)data;
		deleteUsers(tmp, tmp->getUsers());
		if (tmp->getAI() != NULL)
			freeaddrinfo(tmp->getAI());
		if (tmp->getListener() != -1)
			close(tmp->getListener());
		tmp->~Server();
		exit (0);
	}
}

void	Command::_die(std::stringstream& completeCommand, User& user) {

    (void)completeCommand;
    if (user.getMode('o') == true)
    {
        shutdownServer(SIGQUIT);
    }
    else{
        sendDirect(user, ERRCODE_NOPRIVILEGES, ERR_NOPRIVILEGES());
    }
}
