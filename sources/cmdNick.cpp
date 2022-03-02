/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:24:04 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/28 18:18:57 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"


void	Command::_nick(std::stringstream& completeCommand, User& user) {

	std::string nickname;

	if (user.getPassGiven() == false)
		user.setIsEnded(true);
	completeCommand >> nickname;
	if (nickname == user.getNick())
		return;
	if (user.getServer().isNicknameKilled(nickname)== true)
	{
		user.getServer().endConnection(user.getFd());
		return ;
	}
	if (user.getServer().findByNickName(user, nickname) != NULL)// && (nickname != user.getNick()))
	{
		sendDirect(user, 433, ERR_NICKNAMEINUSE(nickname));
		return ;
	}
	if (user.getUserOrNickCmd() && !user.getStartMsg())
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
