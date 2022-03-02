/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:53:47 by fdidelot          #+#    #+#             */
/*   Updated: 2022/02/14 17:01:07 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw Server::badArgumentsCountException();

		Server ircServer;

		ircServer.launchServer(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
