/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:57:10 by fdidelot          #+#    #+#             */
/*   Updated: 2022/02/28 19:04:50 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/************************************************************/
/*					Constructor/Destructor					*/
/************************************************************/
Server::Server(void) {

	FD_ZERO(&_masterFds);
	FD_ZERO(&_readFds);
	initHints();
	return ;
}

Server::~Server(void) {

	return ;
}

/************************************************************/
/*					Getters/Setters							*/
/************************************************************/
/*						Getters								*/

std::map<int, User> Server::getUsers(void)
{
	return (_users);
}

int	Server::getCurrentClient(void) const {

	return (_currentClient);
}

User*	Server::getUser(std::string name)
{
	std::map<int, User>::iterator it = _users.begin();
	std::map<int, User>::iterator ite = _users.end();

	for (; it->first != ite->first; it++)
	{
		if (it->second.getNick() == name)
			return (&it->second);
	}
	return (NULL);
}

Channel*	Server::getChannel(std::string name)
{
	Channel_map_it it = _channels.find(name);
	if (it == _channels.end())
		return (NULL);
	return (&it->second);
}

std::string Server::getPassword(){

	return (this->_password);
}

std::vector<std::string> Server::getUnavalaibleNames()
{
	return (this->_unavalaibleNames);
}

/*						Setters								*/

void Server::setUnavalaibleName(std::string name)
{
	if (std::find(_unavalaibleNames.begin(), _unavalaibleNames.end(), name) != _unavalaibleNames.end())
		return ;
	_unavalaibleNames.push_back(name);
}

/************************************************************/
/*					Members functions						*/
/************************************************************/

bool	Server::isNicknameKilled(std::string name)
{
	if (std::find(_unavalaibleNames.begin(), _unavalaibleNames.end(), name) != _unavalaibleNames.end())
		return true;
	return false;
}

User    *Server::findByNickName(User& user, std::string name)
{
    std::map<int, User> tmp = user.getServer().getUsers();
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

void	Server::initHints(void) {

	bzero(&_hints, sizeof(_hints));
	_hints.ai_family = AF_UNSPEC;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_flags = AI_PASSIVE;
}

void	Server::initAi(char* port) {

	int	retGetAddrinfo;

	retGetAddrinfo = getaddrinfo(NULL, port, &_hints, &_ai);
	if (retGetAddrinfo != SUCCESS)
	{
		std::cerr << "ircserv: " << gai_strerror(retGetAddrinfo) << std::endl;
		exit (FAILURE_GETADDRINFO);
	}
}

void	Server::bindToFirst(void) {

	struct addrinfo	*_p;
	int				yes = 1;

	for(_p = _ai; _p != NULL; _p = _p->ai_next)
	{
		_listener = socket(_p->ai_family, _p->ai_socktype, _p->ai_protocol);
		if (_listener < 0)
			continue;
		setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(_listener, _p->ai_addr, _p->ai_addrlen) < 0)
		{
			close(_listener);
			continue;
		}
		break;
	}
	if (_p == NULL)
	{
		std::cerr << "ircserv: failed to bind" << std::endl;
		exit(FAILURE_BINDING);
	}
	freeaddrinfo(_ai);
}

void	Server::tryListen(void) {

	if (listen(_listener, BACKLOG) == -1)
	{
		perror("listen");
		exit(FAILURE_LISTEN);
	}
}

void	Server::runSelect(void) {

	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	if (select(_fdMax + 1, &_readFds, &_writeFds, NULL, NULL) == -1) {
		perror("select");
		exit(FAILURE_SELECT);
	}
}

void*	Server::getInAddr(struct sockaddr *sa) {

	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


void	Server::newConnection(void) {

	socklen_t				addrLen;
	struct sockaddr_storage	remoteAddr;
	int						newFd;
	char					remoteIP[INET6_ADDRSTRLEN];

	addrLen = sizeof remoteAddr;
	newFd = accept(_listener, (struct sockaddr *)&remoteAddr, &addrLen);
	if (newFd == -1)
		perror("accept");
	else
	{
		FD_SET(newFd, &_masterFds); // add to master set
		_users[newFd] = User(newFd, this);
		if (newFd > _fdMax)
			_fdMax = newFd;
		std::cout	<< "ircserv: new connection from "
					<< 	inet_ntop(remoteAddr.ss_family, getInAddr((struct sockaddr*)&remoteAddr),
									remoteIP, INET6_ADDRSTRLEN)
					<< " on socket "
					<< newFd
					<< std::endl;
	}
}

void	Server::endConnection(int currentSocket) {

	if (_nbytes == 0)
		std::cout << "ircserv: socket " << currentSocket << " hung up" << std::endl;
	else
		perror("recv");
	std::cout << "Delete: " << _users[currentSocket].getNick() << std::endl;
	_users.erase(currentSocket);
	close(currentSocket);
	FD_CLR(currentSocket, &_masterFds);
}

void	Server::createChannel(std::string name)
{
	_channels[name] = Channel(name);
}

void	Server::launchServer(char* port, char* password) {

	_password = password;
	initAi(port); // getaddrinfo
	bindToFirst(); // bind listener
	tryListen(); // try to listen on the opened port
	FD_SET(_listener, &_masterFds); // set the listener fd to the master set
	_fdMax = _listener; // set the maximum fd possible
	while (1)
	{
		_readFds = _masterFds; // copy the master to manipulate
		_writeFds = _readFds;
		runSelect(); // runs select(2)
		for (_currentClient = 0; _currentClient <= _fdMax; _currentClient++)
		{
			if (FD_ISSET(_currentClient, &_readFds))
			{
				if (_currentClient == _listener)
					newConnection();
				else
				{
					bzero(&_buf, sizeof(_buf));
					_nbytes = recv(_currentClient, _buf, sizeof(_buf), 0);
					if (_nbytes < 1)
					{
						std::cout << "mais pas la" << std::endl;
						endConnection(_currentClient);
					}
					else
						_users[_currentClient].handleCommand(_buf);
				}
			}
		}
	}
}

void	Server::sendCommand(int fd, std::string message)
{
	if (FD_ISSET(fd, &_writeFds))
		send(fd, message.c_str(), message.size(), SEND_OPT);
	else
		endConnection(fd);
}
