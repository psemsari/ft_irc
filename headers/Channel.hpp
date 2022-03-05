/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:05:02 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/05 17:00:06 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include "Command.hpp"
# include <list>

class User;

class Command;

class Channel
{
	public:
		typedef std::list<User *> users_list; // à refaire avec des references

	public:
		Channel(){}
		Channel(std::string name);
		~Channel();
		std::string getName();
		users_list&	getList();
		std::string getTopic();
		bool getModeI();
		bool getModeK();
		std::string getModes();
		std::string getPass();
		void setName(std::string name);
		void setModeI(bool mode);
		void setModeK(bool mode);
		void setTopic(std::string topic);
		void setPass(std::string pass);
		void clearPass();
		bool addToChannel(User *user, std::list<std::string> &pass, bool invite);
		void addToInvite(User *user);
		void removeFromChannel(User *user);
		void sendToChannel(std::string str, Command &command, int notsend);
		std::string usersFormat();
		bool inListRm(User &user);
		bool inList(User &user);
		bool inChannel(User &user);

	private:
		bool		_mode_i;
		bool		_mode_k;
		std::string	_name;
		std::string	_topic;
		std::string	_pass;
		users_list	_users;
		users_list	_invite;
};

#endif
