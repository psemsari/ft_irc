/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:47:37 by bemoreau          #+#    #+#             */
/*   Updated: 2022/03/04 20:32:33 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_user(std::stringstream& completeCommand, User& user) {

	std::string username;
	std::string mode;
	std::string unused;
	std::string realname;
	std::string cmd = "USER";
	std::string buf;

	completeCommand >> username >> mode >> unused;

	completeCommand >> buf;
	if (user.getPassGiven() == false)
	{
		sendDirect(user, PONG, ":"+ std::string(SERV_NAME) + " NOTICE " + user.getNick() + " You need to enter the Password server before registration\r\n");
		return;
	}
	while (buf.empty() == false)
	{
		realname += buf;
		realname += ' ';
		buf.clear();
		completeCommand >> buf;	
	}
	if (username.empty() || mode.empty() || unused.empty() || realname.empty())
	{
		sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(cmd));
		return ;
	}
	if (username == DEFAULT_NICKNAME )
	{
		sendCommand(user, ERRCODE_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME(username));
		return ;
	}
	if (realname == DEFAULT_NICKNAME)
	{
		sendCommand(user, ERRCODE_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME(realname));
		return ;
	}
	if (realname[0] == ':')
		realname.erase(0, 1);
	user.setRealname(realname);
	if (user.getUsername() == DEFAULT_NICKNAME)
		user.setUsername(username);
	else
	{
	 	sendDirect(user, ERRCODE_ALREADYREGISTRED, ERR_ALREADYREGISTRED());
		return;
	}
	if (mode == "8")
		user.setMode(true, "i");
	if (user.getUserOrNickCmd() && !user.getStartMsg())
	{
		sendStartMsgs(user);
		user.setStartMsg(true);
	}
	user.setUserOrNickCmd(true);
}