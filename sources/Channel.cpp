/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:09:45 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/04 20:21:10 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name) : _mode_i(false), _mode_k(false), _name(name), _topic(""), _pass("")
{
}

Channel::~Channel()
{
}

//get

std::string Channel::getName()
{
	return (_name);
}

Channel::users_list& Channel::getList()
{
	return (_users);
}

std::string Channel::getTopic()
{
	return (_topic);
}

bool Channel::getModeI()
{
	return (_mode_i);
}

bool Channel::getModeK()
{
	return (_mode_k);
}

std::string Channel::getModes()
{
	std::string modes;

	if (_mode_i)
		modes += "i";
	if (_mode_k)
		modes += "k";
	return ("+" + modes);
}

std::string Channel::getPass()
{
	return (_pass);
}

void Channel::setPass(std::string pass)
{
	_pass = pass;
}

//set

void Channel::setName(std::string name)
{
	_name = name;
}

void Channel::setModeI(bool mode)
{
	_mode_i = mode;
}

void Channel::setModeK(bool mode)
{
	_mode_k = mode;
}

void Channel::setTopic(std::string topic)
{
	_topic = topic;
}


//others

bool Channel::addToChannel(User *user, std::list<std::string> &pass)
{
	if (_mode_k && pass.empty() && pass.front() != _pass)
		return (false);
	_users.push_back(user);
	return (true);
}

void Channel::addToInvite(User *user)
{
	_invite.push_back(user);
}

void Channel::removeFromChannel(User *user)
{
	_users.remove(user);
}

void Channel::sendToChannel(std::string str, Command &command, int notsend)
{
	users_list::iterator it = _users.begin();
	users_list::iterator ite = _users.end();
	for (; it != ite; it++)
		if ((*it)->getFd() != notsend)
			command.sendDirect(**it, PONG, str);
}

void Channel::addOpToChannel(User *user)
{
	_opers.push_back(user);
}

std::string Channel::usersFormat()
{
	Channel::users_list::iterator it = _users.begin();
	Channel::users_list::iterator ite = _users.end();
	std::string ret;
	ret += (*it)->getNick();
	it++;
	for (;it != ite; it++)
	{
		ret += " " + (*it)->getNick();
	}
	return ret;
}

bool Channel::inList(User &user)
{
	Channel::users_list::iterator it = _invite.begin();
	Channel::users_list::iterator ite = _invite.end();
	for (; it != ite; it++)
	{
		if ((*it)->getNick() == user.getNick())
		{
			_invite.erase(it);
			return (true);
		}
	}
	return (false);
}

bool Channel::inChannel(User &user)
{
	Channel::users_list::iterator it = _users.begin();
	Channel::users_list::iterator ite = _users.end();
	for (; it != ite; it++)
	{
		if ((*it)->getNick() == user.getNick())
			return (true);
	}
	return (false);
}
