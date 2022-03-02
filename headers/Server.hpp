/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:58:08 by fdidelot          #+#    #+#             */
/*   Updated: 2022/02/28 14:53:23 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/types.h> // getaddrinfo
# include <sys/socket.h> // getaddrinfo
# include <netdb.h> // getaddrinfo

# include <algorithm>
# include <stdexcept> // exception
# include <iostream> // cerr,cout,endl
# include <cstdlib> // exit
# include <cstring> // bzero
# include <unistd.h> // close
# include <stdio.h> // perror
# include <sstream> // flefleche
# include <map> // map
# include <ctime> // time()


// getaddrinfo, bind, select, accept
# include <stdlib.h>
# include <string>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <vector>
//

# define SERV_NAME "Cthulhu"
# define SERV_VERSION "0.1"
# define CREATION_DATE "Today"

# define MOTD "Welcome to our ft_irc server !"

# define OPERNAME "ircserver"
# define OPERPASS "karmineCorp"

# define SUCCESS 0
# define SUCCESS_ADD 1
# define FAILURE_ADD 0
# define FAILURE_GETADDRINFO 1
# define FAILURE_BINDING 2
# define FAILURE_LISTEN 3
# define FAILURE_SELECT 4
# define ERROR -1
# define SEND_OPT 0
# define BACKLOG 10   // how many pending connections queue will hold
# define SEND_OPT 0

# include "Command.hpp"
# include "User.hpp"
# include "Channel.hpp"

class User;
class Channel;

class Server {

	public:
		typedef std::map<std::string, Channel> Channel_map;
		typedef std::map<std::string, Channel>::iterator Channel_map_it;

	public:

		Server(void);
		~Server(void);

		User    *findByNickName(User& user, std::string name);
		bool	isNicknameKilled(std::string name);
		void	launchServer(char* port, char* password);
		void	initHints(void);
		void	initAi(char* port);
		void	bindToFirst(void);
		void	tryListen(void);
		void	runSelect(void);
		void	newConnection(void);
		void	endConnection(int currentSocket);
		void*	getInAddr(struct sockaddr* sa);
		void	execCommand(std::string commandLine);
		void	sendCommand(int fd, std::string message);
		User*	getUser(std::string name);
		std::map<int, User> getUsers(void);
		Channel*	getChannel(std::string name);
		std::string		getPassword();
		std::vector<std::string>	getUnavalaibleNames();
		void	setUnavalaibleName(std::string name);

		int		getCurrentClient(void) const;
		Channel_map& getChannelMap(void)
		{
			return (_channels);
		}

		void	createChannel(std::string name);
		void	eraseChannel(std::string name)
		{
			_channels.erase(name);
		}

		class badArgumentsCountException : public std::exception {

			public:

				const char* what() const throw() {

					return ("Wrong number of arguments\n"
								"Usage : ./ircserv <port> <password>");
				}
		};

	private:

		fd_set				_masterFds;			// master file descriptor list
		fd_set				_readFds;			// temporary file descriptor list for select(2)
		fd_set				_writeFds;			// check if i can write on fd
		struct addrinfo		_hints; 			// hint struct for getaddrinfo to set _ai
		struct addrinfo		*_ai;				// list of struct given by getaddrinfo use for binding
		int					_listener;			// listening socket descriptor
		int					_fdMax;				// maximum file descriptor number
		int					_nbytes;			// number of bytes read
		std::string			_password; 			// password defined by the server
		std::vector<std::string> _unavalaibleNames; // list of Unavalaible names (KILLed ones)
		char				_buf[256];			// buffer for client data
		int					_currentClient; 	// store the current client fd
		std::map<int, User>	_users; 			// list of users associate with fd
		Channel_map			_channels;			// list of channels associate with names
};

#endif
