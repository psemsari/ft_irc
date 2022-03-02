#include "Command.hpp"

bool findByNickName(User& user, std::string name)
{
    std::map<int, User> tmp = user.getServer().getUsers();
    std::map<int, User>::iterator it = tmp.begin();
    std::map<int, User>::iterator ite = tmp.end();
    while (it != ite)
    {
        if (it->second.getNick() == name)
            return (true);
        it++;
    }
    return false;
}

void    Command::printUserData(User& user, User *target)
{
    std::string nick = target->getNick();
    std::string username = target->getUsername();
    std::string host = SERV_NAME;
    std::string realname = target->getRealname();

    sendCommand(user, RPLCODE_WHOISUSER, RPL_WHOISUSER(nick, username, host, realname));
    
    std::list<Channel *> tmp =  target->getChannelList();
    std::list<Channel *>::iterator it = tmp.begin();
    std::list<Channel *>::iterator ite = tmp.end();

    std::string buffer;
    while (it != ite)
    {
        buffer += (*it)->getName();
        buffer += ' ';
        it++;
    }
    if (buffer.empty() == false)
    {
        buffer.erase(buffer.length() - 1, buffer.length());
        sendCommand(user, RPLCODE_WHOISCHANNELS, RPL_WHOISCHANNELS(user.getNick(), buffer)); // A remplacer par le topic du chann
    }
    if (target->getMode('o') == true)
        sendCommand(user, RPLCODE_WHOISOPERATOR, RPL_WHOISOPERATOR(nick));
    //    sendCommand(user, RPLCODE_WHOISIDLE, RPL_WHOISIDLE()) Je sais pas, signon relou mais le reste ez
    sendCommand(user, RPLCODE_ENDOFWHOIS, RPL_ENDOFWHOIS(nick));
}

void	Command::_whois(std::stringstream& completeCommand, User& user) {

    //Add idle ?

    //(void)completeCommand; (void)user;
	std::string mask;
    std::string comma;
    
    completeCommand >> mask;
    while (!(mask.empty()))
    {
        if ((findByNickName(user, mask)) == true)
        {
            printUserData(user, user.getServer().getUser(mask));
        }
        else
        {
            sendCommand(user, ERRCODE_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN());
            return;
        }
        completeCommand >> comma;
        if (comma.empty() || comma != ",")
            return;
        completeCommand >> mask;
    }
}
