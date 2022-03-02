#include "Command.hpp"

void	Command::_kill(std::stringstream& completeCommand, User& user)
{
    std::string cmd = "KILL";
    std::string nick;
    std::string message;
    User *target;

    completeCommand >> nick;
    completeCommand >> message;
    if (user.getMode('o') == false)
    {
        sendCommand(user, ERRCODE_NOPRIVILEGES, ERR_NOPRIVILEGES());
        return ;
    }
    if (nick.empty() == true || message.empty())
    {
        sendCommand(user, ERRCODE_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(cmd));
        return ;
    }
    if (nick == SERV_NAME)
    {
        sendCommand(user, ERRCODE_CANTKILLSERVER, ERR_CANTKILLSERVER());
        return ;
    }
    target = user.getServer().findByNickName(user, nick);
    if (!target)
    {
        sendCommand(user, ERRCODE_NOSUCHNICK, ERR_NOSUCHNICK(nick));
        return ;
    }
    sendDirect(*target, PONG, "You have been killed because: " + message);
    user.getServer().setUnavalaibleName(nick);
    target->getServer().endConnection(target->getFd());
}