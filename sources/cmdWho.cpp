/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdWho.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:47:29 by bemoreau          #+#    #+#             */
/*   Updated: 2022/03/02 12:47:29 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"


std::string createUserDataBuff(User *usr)
{
	std::string buff;

	buff += "~u";
	buff += " ";
	buff += "localhost";
	buff += " ";
	buff += SERV_NAME;
	buff += " ";
	buff += usr->getNick();
	buff += " : ";
	buff += usr->getRealname();
	return buff;
}

bool     findCommonChannel(User u1, User u2)
{
	std::list<Channel *> tmp = u1.getChannelList();
	std::list<Channel *>::iterator it1 = tmp.begin();
	std::list<Channel *>::iterator ite1 = tmp.end();

	tmp = u2.getChannelList();
	std::list<Channel *>::iterator it2 = tmp.begin();
	std::list<Channel *>::iterator ite2 = tmp.end();
	while (it1 != ite1)
	{
		while (it2 != ite2)
		{
			if ((*it1)->getName() == (*it2)->getName())
				return (false);
			it2++;
		}
		it2 = u2.getChannelList().begin();
		it1++;
	}
	return (true);
}

User    *findByNickname(User *user, std::string name)
{
	std::map<int, User> tmp = user->getServer().getUsers();
	std::map<int, User>::iterator it = tmp.begin();
	std::map<int, User>::iterator ite = tmp.end();
	while (it != ite)
	{
		if (it->second.getNick() == name)
			return (&(it->second));
		it++;
	}
	return NULL;
}

bool Command::findByUsername(User& user, std::string name, bool oper)
{
	std::map<int, User> tmp = user.getServer().getUsers();
	std::map<int, User>::iterator it = tmp.begin();
	std::map<int, User>::iterator ite = tmp.end();
	bool ret = false;
	while (it != ite)
	{
		if (it->second.getUsername() == name)
			if ((oper == false || it->second.getMode('o') == true) && user.getMode('i') == false)
				ret = true;
		it++;
	}
	return ret;
}

std::string findByChannel(User *u1, std::string mask)
{
	std::list<Channel *> tmp = u1->getChannelList();
	std::list<Channel *>::iterator it = tmp.begin();
	std::list<Channel *>::iterator ite = tmp.end();

	std::string ret;
	ret.clear();

	while (it != ite)
	{
		if ((*it)->getName() == mask)
			return ((*it)->getName());
		it++;
	}
	return (ret);
}

bool    Command::findNicknameOccurence(User& user, std::map<int, User> users, bool oper, std::string mask)
{
	std::map<int, User>::iterator it = users.begin();
	std::map<int, User>::iterator ite = users.end();
	while (it != ite)
	{
		if (it->second.getNick() == mask)
			if ((oper == false || user.getMode('o') == true) && user.getMode('i') == false)
			{
				return true;
			}
		it++;
	}
	return false;
}

void	Command::_who(std::stringstream& completeCommand, User& user) {

	std::string mask;
	std::string tmp;

	completeCommand >> mask >> tmp;
	bool o = (tmp == "o") ? true : false;
	if (mask.empty() == true || mask == "0")
	{
		std::map<int, User> tmp = user.getServer().getUsers();
		std::map<int, User>::iterator it = tmp.begin();
		std::map<int, User>::iterator ite = tmp.end();
		while (it != ite)
		{
			if (it->second.getMode('i') == false)
				if (findCommonChannel(user, it->second) == true)
					if (o == false || it->second.getMode('o') == true)
						sendCommand(user, RPLCODE_WHOREPLY, RPL_WHOREPLY(createUserDataBuff(&(it->second))));
			it++;
		}
		sendCommand(user, RPLCODE_ENDOFWHO, RPL_ENDOFWHO(user.getNick()));
	}
	else
	{
		if (findByChannel(&user, mask).empty() == false)
		{
			std::map<int, User> temp = user.getServer().getUsers();
			std::map<int, User>::iterator it = temp.begin();
			std::map<int, User>::iterator ite = temp.end();

			while (it != ite)
			{
				if ((findByChannel(&(it->second), mask).empty() == false) && (o == false || it->second.getMode('o') == true) && (it->second.getMode('i') == false || (findByChannel(&user, mask).empty() == false)))
					sendCommand(user, RPLCODE_WHOREPLY, RPL_WHOREPLY(createUserDataBuff(&(it->second))));
				it++;
			}
		}
		else if ((findNicknameOccurence(user, user.getServer().getUsers(), o, mask)) == true)
		{
			sendCommand(user, RPLCODE_WHOREPLY, RPL_WHOREPLY(createUserDataBuff(findByNickname(&user, mask))));
		}
		else if ((findByUsername(user, mask, o)) == true)
		{
			std::map<int, User> tmp = user.getServer().getUsers();
			std::map<int, User>::iterator it = tmp.begin();
			std::map<int, User>::iterator ite = tmp.end();
			while (it != ite)
			{
				if (it->second.getUsername() == mask)
					if ((o == false || it->second.getMode('o') == true) && user.getMode('i') == false)
						sendCommand(user, RPLCODE_ENDOFWHO, RPL_ENDOFWHO(createUserDataBuff(&(it->second))));
				it++;
			}
		}
		else if (mask == SERV_NAME)
		{
			std::map<int, User> tmp = user.getServer().getUsers();
			std::map<int, User>::iterator it = tmp.begin();
			std::map<int, User>::iterator ite = tmp.end();

			while (it != ite)
			{
				if ((o == false || it->second.getMode('o') == true) && it->second.getMode('i') == false)
					sendCommand(user, RPLCODE_WHOREPLY, RPL_WHOREPLY(createUserDataBuff(&(it->second))));
				it++;
			}
		}
		sendCommand(user, RPLCODE_ENDOFWHO, RPL_ENDOFWHO(user.getNick()));
	}
}
