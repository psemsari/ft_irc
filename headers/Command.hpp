/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:44:55 by fdidelot          #+#    #+#             */
/*   Updated: 2021/12/16 18:10:47 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "User.hpp"
# define NB_COMMAND 21 //add if command
# define EOT_CODE 4

// Error codes
# define ERRCODE_NOSUCHNICK			401
# define ERRCODE_NOSUCHSERVER		402
# define ERRCODE_NOSUCHCHANNEL		403
# define ERRCODE_CANNOTSENDTOCHAN	404
# define ERRCODE_TOOMANYCHANNELS	405
# define ERRCODE_WASNOSUCHNICK		406
# define ERRCODE_TOOMANYTARGETS		407
# define ERRCODE_NOORIGIN			409
# define ERRCODE_NORECIPIENT		411
# define ERRCODE_NOTEXTTOSEND		412
# define ERRCODE_NOTOPLEVEL			413
# define ERRCODE_WILDTOPLEVEL		414
# define ERRCODE_UNKNOWNCOMMAND		421
# define ERRCODE_NOMOTD				422
# define ERRCODE_NOADMININFO		423
# define ERRCODE_FILEERROR			424
# define ERRCODE_NONICKNAMEGIVEN	431
# define ERRCODE_ERRONEUSNICKNAME	432
# define ERRCODE_NICKNAMEINUSE		433
# define ERRCODE_NICKCOLLISION		436
# define ERRCODE_USERNOTINCHANNEL	441
# define ERRCODE_NOTONCHANNEL		442
# define ERRCODE_USERONCHANNEL		443
# define ERRCODE_NOLOGIN			444
# define ERRCODE_SUMMONDISABLED		445
# define ERRCODE_USERSDISABLED		446
# define ERRCODE_NOTREGISTERED		451
# define ERRCODE_NEEDMOREPARAMS		461
# define ERRCODE_ALREADYREGISTRED	462
# define ERRCODE_NOPERMFORHOST		463
# define ERRCODE_PASSWDMISMATCH		464
# define ERRCODE_YOUREBANNEDCREEP	465
# define ERRCODE_KEYSET				467
# define ERRCODE_CHANNELISFULL		471
# define ERRCODE_UNKNOWNMODE		472
# define ERRCODE_INVITEONLYCHAN		473
# define ERRCODE_BANNEDFROMCHAN		474
# define ERRCODE_BADCHANNELKEY		475
# define ERRCODE_NOPRIVILEGES		481
# define ERRCODE_CHANOPRIVSNEEDED	482
# define ERRCODE_CANTKILLSERVER		483
# define ERRCODE_NOOPERHOST			491
# define ERRCODE_UMODEUNKNOWNFLAG	501
# define ERRCODE_USERSDONTMATCH		502
# define ERRCODE_INVALIDCAP
# define ERRCODE_NOTOPIC
# define ERRCODE_BADCHANMASK
# define ERRCODE_ALREADYBAN
# define ERRCODE_SERVERISFULL
# define ERRCODE_KILLDENY

// Error messages
# define ERR_NOSUCHNICK(pseudo) (pseudo + " :No such nick/channel\r\n") //401
# define ERR_NOSUCHSERVER(server) (server + " :No such server\r\n") //402
# define ERR_NOSUCHCHANNEL(channel) (channel + " :No such channel\r\n") //403
# define ERR_CANNOTSENDTOCHAN(channel) (channel + " :Cannot send to channel\r\n") //404
# define ERR_TOOMANYCHANNELS(channel) (channel + " :You have joined too many channels\r\n") //405
# define ERR_WASNOSUCHNICK(nickname) (nickname + " :There was no such nickname\r\n") //406
# define ERR_TOOMANYTARGETS(dest) (dest + ":Duplicate recipients. No message delivered\r\n") //407
# define ERR_NOORIGIN() (":No origin specified\r\n") //409
# define ERR_NORECIPIENT(command) (":No recipient given (" + command + ")\r\n")
# define ERR_NOTEXTTOSEND() (":No text to send\r\n")
# define ERR_NOTOPLEVEL(mask) (mask + " :No toplevel domain specified\r\n")
# define ERR_WILDTOPLEVEL(mask) (mask + " :Wildcard in toplevel domain\r\n")
# define ERR_UNKNOWNCOMMAND(command) (command + " :Unknown command\r\n")
# define ERR_NOMOTD() (":MOTD File is missing\r\n")
# define ERR_NOADMININFO(server) (server + " :No administrative info available\r\n")
# define ERR_FILEERROR(operation, file) (":File error doing " + operation + " on " + file + "\r\n")
# define ERR_NONICKNAMEGIVEN() (":No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(pseudo) (pseudo + " :Erroneus nickname\r\n")
# define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use\r\n")
# define ERR_NICKCOLLISION(nick, user, host) (nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n")
# define ERR_USERNOTINCHANNEL(pseudo, channel) (pseudo + " :Is not on channel " + channel + "\r\n")
# define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel\r\n")
# define ERR_USERONCHANNEL(user, channel) (user + channel + " :User is already on that channel\r\n")
# define ERR_NOLOGIN(user) (user + " :User not logged in\r\n")
# define ERR_SUMMONDISABLED() (":SUMMON has been disabled\r\n")
# define ERR_USERSDISABLED() (":USERS has been disabled\r\n")
# define ERR_NOTREGISTERED() (":You have not registered\r\n")
# define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters\r\n") // 461
# define ERR_ALREADYREGISTRED() (":Unauthorized command (already registered)\r\n") // 462
# define ERR_NOPERMFORHOST() (":Your host isn't among the privileged\r\n")
# define ERR_PASSWDMISMATCH() (":Password incorrect\r\n") // 464
# define ERR_YOUREBANNEDCREEP() (":You are banned from this server\r\n")
# define ERR_KEYSET(channel) (channel + " :Channel key already set\r\n")
# define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)\r\n")
# define ERR_UNKNOWNMODE(character) (character + " :is unknown mode char to me\r\n")
# define ERR_INVITEONLYCHAN(channel) (channel + " :Cannot join channel (+i)\r\n")
# define ERR_BANNEDFROMCHAN(channel) (channel + " :Cannot join channel (+b)\r\n")
# define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)\r\n")
# define ERR_NOPRIVILEGES() (":Permission Denied- You're not an IRC operator\r\n") // 481
# define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator\r\n")
# define ERR_CANTKILLSERVER() (":You cant kill a server!\r\n")
# define ERR_NOOPERHOST() (":No O-lines for your host\r\n")
# define ERR_UMODEUNKNOWNFLAG() (":Unknown MODE flag\r\n")
# define ERR_USERSDONTMATCH() (":Cannot change mode for other users\r\n")
# define ERR_INVALIDCAP(command) (command + " :Invalid CAP command\r\n")
# define ERR_NOTOPIC(channel) (channel + " :No topic is set\r\n")
# define ERR_BADCHANMASK(channel) (channel + " :Bad Channel Mask\r\n")
# define ERR_ALREADYBAN(channel, user) (channel + " " + user + " b :Channel " + channel + " list already contains " + user + "\r\n")
# define ERR_SERVERISFULL(serv_name) (serv_name + " Server is full\r\n");
# define ERR_KILLDENY(mssg) (":" + mssg + "\r\n")

/*
**  reponse for command file
*/
// Handmade responses
# define PONG			-1
# define PONG_MSG(servName) (":" + servName + " PONG " + servName + " :" + servName + "\r\n")
# define NICK_MSG(nick, user_name) (":" + user_name + "! NICK " + nick + "\r\n")

// Response codes
# define RPLCODE_MESSAGE
# define RPLCODE_WELCOME			1
# define RPLCODE_YOURHOST			2
# define RPLCODE_CREATED			3
# define RPLCODE_MYINFO				4
# define RPLCODE_BOUNCE				5
# define RPLCODE_NONE				300
# define RPLCODE_USERHOST			302
# define RPLCODE_ISON				303
# define RPLCODE_AWAY				301
# define RPLCODE_UNAWAY				305
# define RPLCODE_NOWAWAY			306
# define RPLCODE_WHOISUSER			311
# define RPLCODE_WHOISOPERATOR		313
# define RPLCODE_WHOISIDLE			317
# define RPLCODE_WHOREPLY			352
# define RPLCODE_ENDOFWHOIS			318
# define RPLCODE_WHOISCHANNELS		319
# define RPLCODE_WHOWASUSER			314
# define RPLCODE_ENDOFWHOWAS		369
# define RPLCODE_LISTSTART			321
# define RPLCODE_LIST				322
# define RPLCODE_LISTEND			323
# define RPLCODE_CHANNELMODEIS		324
# define RPLCODE_NOTOPIC			331
# define RPLCODE_TOPIC				332
# define RPLCODE_INVITING			341
# define RPLCODE_SUMMONING			342
# define RPLCODE_VERSION			351
# define RPLCODE_ENDOFWHO			315
# define RPLCODE_NAMREPLY			353
# define RPLCODE_ENDOFNAMES			366
# define RPLCODE_LINKS				364
# define RPLCODE_ENDOFLINKS			365
# define RPLCODE_BANLIST			367
# define RPLCODE_ENDOFBANLIST		368
# define RPLCODE_INFO				371
# define RPLCODE_ENDOFINFO			374
# define RPLCODE_MOTDSTART			375
# define RPLCODE_MOTD				372
# define RPLCODE_ENDOFMOTD			376
# define RPLCODE_YOUREOPER			381
# define RPLCODE_REHASHING			382
# define RPLCODE_TIME				391
# define RPLCODE_USERSSTART			392
# define RPLCODE_ENDOFUSERS			394
# define RPLCODE_NOUSERS			395
# define RPLCODE_TRACELINK			200
# define RPLCODE_TRACECONNECTING	201
# define RPLCODE_TRACEHANDSHAKE		202
# define RPLCODE_TRACEUNKNOWN		203
# define RPLCODE_TRACEOPERATOR		204
# define RPLCODE_TRACEUSER			205
# define RPLCODE_TRACESERVER		206
# define RPLCODE_TRACENEWTYPE		208
# define RPLCODE_TRACELOG			261
# define RPLCODE_TRACEEND			262
# define RPLCODE_STATSLINKINFO		211
# define RPLCODE_STATSCOMMANDS		212
# define RPLCODE_STATSCLINE			213
# define RPLCODE_STATSNLINE			214
# define RPLCODE_STATSILINE			215
# define RPLCODE_STATSKLINE			216
# define RPLCODE_STATSYLINE			218
# define RPLCODE_ENDOFSTATS			219
# define RPLCODE_STATSLLINE			241
# define RPLCODE_STATSUPTIME		242
# define RPLCODE_STATSOLINE			243
# define RPLCODE_STATSHLINE			244
# define RPLCODE_UMODEIS			221
# define RPLCODE_LUSERCLIENT		251
# define RPLCODE_LUSEROP			252
# define RPLCODE_LUSERUNKNOWN		253
# define RPLCODE_LUSERCHANNELS		254
# define RPLCODE_LUSERME			255
# define RPLCODE_ADMINME			256
# define RPLCODE_ADMINLOC1			257
# define RPLCODE_ADMINLOC2			258
# define RPLCODE_ADMINEMAIL			259
# define RPLCODE_CREATIONTIME
# define RPLCODE_YOURESERVICE		383

// Response text
# define RPL_MESSAGE(servName, number, nick) (":" + servName + " " + number + " " + nick + " ")
# define RPL_MYINFO(servName, servVersion) (":" + servName + " " + servVersion + " user_mode, channel modes" + "\r\n")
# define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick + "\r\n")
# define RPL_YOURHOST(servName, servVersion) (":Your host is " + servName + ", running version " + servVersion + "\r\n")
# define RPL_CREATED(date) (":This server was created " + date + "\r\n")
# define RPL_BOUNCE(server_name, port) ("Try server " + server_name + ", port " + port + "\r\n")
# define RPL_NONE() ("\r\n") //300
# define RPL_USERHOST(userhost_list) (userhost_list + "\r\n") //<réponse> ::= <pseudo>['*'] '=' <'+'|'-'><hôte>
# define RPL_ISON(user_list) (user_list + "\r\n")
# define RPL_AWAY(pseudo, str) (pseudo + " " + str + "\r\n")
# define RPL_UNAWAY() (":You are no longer marked as being away\r\n")
# define RPL_NOWAWAY() (":You have been marked as being away\r\n")
# define RPL_WHOISUSER(nick, user, host, realname) (nick + " " + user + " " + host + " * :" + realname + "\r\n")
# define RPL_WHOISOPERATOR(pseudo) (pseudo + " :is an IRC operator\r\n")
# define RPL_WHOISIDLE(pseudo, idle, signon) (pseudo + " " + idle + " " + signon + " :seconds idle, signon time\r\n")
# define RPL_WHOREPLY(arg) (arg + "\r\n")
# define RPL_ENDOFWHOIS(pseudo) (pseudo + " :End of /WHOIS list\r\n")
# define RPL_WHOISCHANNELS(nick, chann_info) (nick + " :" + chann_info + "\r\n")
# define RPL_WHOWASUSER(nick, user, host, realname) (nick + " " + user + " " + host + " * :" + realname + "\r\n")
# define RPL_ENDOFWHOWAS(nick) (nick + " :End of WHOWAS\r\n")
# define RPL_LISTSTART() ("Channel :Users Name\r\n")
# define RPL_LIST(channel, topic) (channel + " :" + topic + "\r\n")
# define RPL_LISTEND() (":End of LIST\r\n")
# define RPL_CHANNELMODEIS(channel, mode, params) (channel + " " + mode + " " + params + "\r\n")
# define RPL_NOTOPIC(channel) (channel + " :No topic is set\r\n")
# define RPL_TOPIC(channel, subject) (channel + " :" + subject + "\r\n")
# define RPL_INVITING(channel, pseudo) (channel + " " + pseudo + "\r\n")
# define RPL_SUMMONING(user) (user + " :Summoning user to IRC\r\n")
# define RPL_VERSION(version, debuglevel, server, comment) (version + "." + debuglevel + " " + server + " :" + comment + "\r\n")
# define RPL_ENDOFWHO(name) (name + " :End of WHO list\r\n")
# define RPL_NAMREPLY(channel, nick_list) (channel + " :" + nick_list + "\r\n") //modif_ici
# define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list\r\n")
# define RPL_LINKS(mask, server_name, hopcount, info) (mask + " " + server_name + " " + hopcount + " " + info + "\r\n")
# define RPL_ENDOFLINKS(mask) (mask + " :End of LINKS list\r\n")
# define RPL_BANLIST(mssg) (mssg + "\r\n")
# define RPL_ENDOFBANLIST(channel) (channel + " :End of list\r\n")
# define RPL_INFO(info) (":" + info + "\r\n")
# define RPL_ENDOFINFO() (":End of INFO list\r\n")
# define RPL_MOTDSTART(server) (":- " + server + " Message of the day - \r\n")
# define RPL_MOTD(comment) (":- " + comment + "\r\n")
# define RPL_ENDOFMOTD() (":End of MOTD command\r\n")
# define RPL_YOUREOPER() (":You are now an IRC operator\r\n") // 381
# define RPL_REHASHING(config_file) (config_file + " :Rehashing\r\n")
# define RPL_TIME(server, time_serveur) (server + " :" + time_serveur + "\r\n")
# define RPL_USERSSTART() (":UserID Terminal Hôte\r\n")
# define RPL_ENDOFUSERS() (":End of users\r\n")
# define RPL_NOUSERS() (":Nobody logged in\r\n")
# define RPL_TRACELINK(dest, next_serv) ("Link " + std::string(VERSION) + " " + dest + " " + next_serv + "\r\n")
# define RPL_TRACECONNECTING(classe, server) ("Try. " + classe + " " + server + "\r\n")
# define RPL_TRACEHANDSHAKE(classe, server) ("H.S. " + classe + " " + serveur + "\r\n")
# define RPL_TRACEUNKNOWN(pseudo) ("???? 1 " + pseudo + "\r\n")
# define RPL_TRACEOPERATOR(pseudo) ("Oper 1 " + pseudo + "\r\n")
# define RPL_TRACEUSER(pseudo) ("User 1 " + pseudo + "\r\n")
# define RPL_TRACESERVER(server_name) ("Serv 1 0S 0C " + server_name + " *!*@" + server_name + " V" + PROTOCOL_VERSION + "\r\n")
# define RPL_TRACENEWTYPE(new_type, name) (new_type + " 0 " + name + "\r\n")
# define RPL_TRACELOG(file_log, debug_level) ("File " + file_log + " " + debug_level + "\r\n")
# define RPL_TRACEEND(server_name, version_debug) (server_name + " " + version_debug + " :End of TRACE\r\n")
# define RPL_STATSLINKINFO(arg) (arg + "\r\n")
# define RPL_STATSCOMMANDS(arg) (arg + "\r\n")
# define RPL_STATSCLINE(host, name, port, classe) ("C " + host + " * " + name + " " + port + " " + classe + "\r\n")
# define RPL_STATSNLINE(host, name, port, classe) ("N " + host + " * " + name + " " + port + " " + classe + "\r\n")
# define RPL_STATSILINE(host, port, classe) ("I " + host + " * " + host + " " + port + " " + classe + "\r\n")
# define RPL_STATSKLINE(host, user_name, port, classe) ("K " + host + " * " + user_name + " " + port + " " + classe + "\r\n")
# define RPL_STATSYLINE(classe, frq_ping, frq_connection, sendq_max) ("Y " + classe + " " + frq_ping + " " + frq_connection + " " + sendq_max + "\r\n")
# define RPL_ENDOFSTATS(stat_letter) (stat_letter + " :End of STATS report\r\n")
# define RPL_STATSLLINE(host_mask, server_name, max_depth) ("L " + host_mask + " * " + server_name + max_depth "\r\n")
# define RPL_STATSUPTIME(arg) (":Server Up " + arg + "\r\n")
# define RPL_STATSOLINE(host_mask, name) ("O " + host_mask + " * " + name + "\r\n")
# define RPL_STATSHLINE(host_mask, server_name) ("H " + host_mask + " * " + server_name + "\r\n")
# define RPL_UMODEIS(user_mode) ("+" + user_mode + "\r\n")
# define RPL_LUSERCLIENT(int1, int2, int3) (":There are " + int1 + " users and " + int2 + " invisible on " + int3 + " servers\r\n")
# define RPL_LUSEROP(int1) (int1 + " :operator(s) online\r\n")
# define RPL_LUSERUNKNOWN(int1) (int1 + " :unknown connection(s)\r\n")
# define RPL_LUSERCHANNELS(int1) (int1 + " :channels formed\r\n")
# define RPL_LUSERME(int1, int2) (":I have " + int1 + " clients and " + int2 + " servers\r\n")
# define RPL_ADMINME(server) (server + " :Administrative info\r\n")
# define RPL_ADMINLOC1(info) (":" + info + "\r\n")
# define RPL_ADMINLOC2(info) (":" + info + "\r\n")
# define RPL_ADMINEMAIL(info) (":" + info + "\r\n")
# define RPL_CREATIONTIME(channel, c_time) (channel + " " + c_time + "\r\n")
# define RPL_YOURESERVICE(servicename) (":You are service " + servicename + "\r\n")

class User;

class Command
{
	public:

		Command(std::string commandName = "Unknown");
		~Command(void);

		void    printUserData(User& user, User *target);
		bool	findByUsername(User& user, std::string name, bool oper);
		void    listUsersFromChannel(User usr, std::map<int, User> users, std::string chan, bool oper);
		bool	findNicknameOccurence(User& user, std::map<int, User> users, bool oper, std::string mask);
		void    showAllUsers(User usr, std::map<int, User> users, bool oper);
		void	launchCommand(std::stringstream& completeCommand, User& user);
		void	sendCommand(User& user, int msgId, std::string toSend) const;
		void	sendDirect(User& user, int msgId, std::string toSend) const;
		void	sendStartMsgs(User& user) const;

	private:

		std::string	_type;
		void		_pass(std::stringstream& completeCommand, User& user);
		void		_nick(std::stringstream& completeCommand, User& user);
		void		_user(std::stringstream& completeCommand, User& user);
		void		_cap(std::stringstream& completeCommand, User& user);
		void		_mode(std::stringstream& completeCommand, User& user);
		void		_join(std::stringstream& completeCommand, User& user);
		void		_ping(std::stringstream& completeCommand, User& user);
		void		_privmsg(std::stringstream& completeCommand, User& user);
		void		_part(std::stringstream& completeCommand, User& user);
		void		_quit(std::stringstream& completeCommand, User& user);
		void		_list(std::stringstream& completeCommand, User& user);
		void		_names(std::stringstream& completeCommand, User& user);
		void		_oper(std::stringstream& completeCommand, User& user);
		void		_motd(std::stringstream& completeCommand, User& user);
		void		_kill(std::stringstream& completeCommand, User& user);
		void		_kick(std::stringstream& completeCommand, User& user);
		void		_who(std::stringstream& completeCommand, User& user);
		void		_whois(std::stringstream& completeCommand, User& user);
		void		_notice(std::stringstream& completeCommand, User& user);
		void		_topic(std::stringstream& completeCommand, User& user);
		void		_invite(std::stringstream& completeCommand, User& user);
};

#endif
