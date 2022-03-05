/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:04 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/05 16:03:52 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"


void	Command::_nick(std::stringstream& completeCommand, User& user) {

	std::string nickname;

	if (user.getPassGiven() == false)
	{
	    sendDirect(user, PONG, ":"+ std::string(SERV_NAME) + " NOTICE " + user.getNick() + "You need to enter the Password server before registration\r\n");
		return ;
	}
	completeCommand >> nickname;
	if (nickname == user.getNick())
		return;
	if (user.getServer().isNicknameKilled(nickname)== true)
	{
		user.setIsEnded(true);
		return ;
	}
	if (user.getServer().findByNickName(user, nickname) != NULL)
	{
		sendDirect(user, 433, ERR_NICKNAMEINUSE(nickname));
		return ;
	}
	if (user.getUserOrNickCmd() && !user.getStartMsg() && (user.getUsername() != DEFAULT_NICKNAME))
	{
		user.setNickname(nickname);
		sendStartMsgs(user);
		user.setStartMsg(true);
	}
	else if (user.getStartMsg())
	{
		sendDirect(user, PONG, NICK_MSG(nickname, user.getNick()));
		user.setNickname(nickname);
	}
	else
		user.setNickname(nickname);
	user.setUserOrNickCmd(true);
}
