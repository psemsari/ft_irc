/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdOper.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:48:18 by bemoreau          #+#    #+#             */
/*   Updated: 2022/03/02 12:48:18 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_oper(std::stringstream& completeCommand, User& user)
{
    std::string cmd = "OPER";
    std::string name;
    std::string pass;

    completeCommand >> name >> pass;
    if (name.empty() || pass.empty())
	{
    	sendCommand(user, 461, ERR_NEEDMOREPARAMS(cmd));
        return;
    }
    if (user.setOperator(name, pass) == 0)
    {
        sendCommand(user, 381, RPL_YOUREOPER());
    }
    else
    {
        sendCommand(user, 464, ERR_PASSWDMISMATCH());
    }

}
