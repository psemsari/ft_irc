/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:43 by bemoreau          #+#    #+#             */
/*   Updated: 2022/03/05 15:54:53 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	*data;

void    deleteAllUsers(Server *srv, std::map<int, User> users)
{
	std::map<int, User>::iterator it = users.begin();
	std::map<int, User>::iterator ite = users.end();

	while (it != ite)
	{
		srv->endConnection(it->second.getFd());
		it++;
	}
}

void	shutdownServer(int sigId)
{
	if (sigId == SIGQUIT || sigId == SIGINT)
	{
		Server *tmp;
		tmp = (Server *)data;
		deleteAllUsers(tmp, tmp->getUsers());
		if (tmp && tmp->getAI() != NULL)
			freeaddrinfo(tmp->getAI());
		if (tmp && tmp->getListener() != -1)
			close(tmp->getListener());
		tmp->~Server();
		exit (0);
	}
}

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw Server::badArgumentsCountException();

		Server ircServer;
		signal(SIGQUIT, &shutdownServer);
		signal(SIGINT, &shutdownServer);
		signal(SIGPIPE, SIG_IGN);
		data = (void *)&ircServer;
		ircServer.launchServer(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
