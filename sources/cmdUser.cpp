/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:47:37 by bemoreau          #+#    #+#             */
/*   Updated: 2022/03/02 12:47:38 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_user(std::stringstream& completeCommand, User& user) {

	std::string username;
	std::string mode;
	std::string unused;
	std::string realname;
	std::string cmd = "USER";


	completeCommand >> username >> mode >> unused;

	if (user.getPassGiven() == false)
		user.setIsEnded(true);
	if (user.getUserOrNickCmd() && !user.getStartMsg())
	{
		sendStartMsgs(user);
		user.setStartMsg(true);
	}
	if (username.empty() == false)
	{
		if (user.getUsername().empty() == true)
			user.setUsername(username);
		else
		{
		 	sendDirect(user, ERRCODE_ALREADYREGISTRED, ERR_ALREADYREGISTRED());
		}
	}
	else{
		sendDirect(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(cmd));
		return ;
	}
	if (mode.empty() == false)
	{
		if (mode == "8")
			user.setMode(true, "i");
	}
	else{
		sendDirect(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(cmd));
		return ;
	}

	std::string buf;
	completeCommand >> buf;
	while (buf.empty() == false)
	{
		realname += buf;
		realname += ' ';
		buf.clear();
		completeCommand >> buf;	
	}
	if (realname.empty() == false)
	{
		if (realname[0] == ':')
			realname.erase(0, 1);
		user.setRealname(realname);
	}
	else
	{
		sendDirect(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(cmd));
		return ;
	}
	user.setUserOrNickCmd(true);
}