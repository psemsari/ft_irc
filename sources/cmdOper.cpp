#include "Command.hpp"

void	Command::_oper(std::stringstream& completeCommand, User& user)
{
    std::string cmd = "OPER";
    std::string name;
    std::string pass;

    //ERR_NOOPERHOST
    completeCommand >> name >> pass;
    if (name.empty() || pass.empty())
		sendCommand(user, 461, ERR_NEEDMOREPARAMS(cmd));
    if (user.setOperator(name, pass) == 0)
    {
        sendCommand(user, 381, RPL_YOUREOPER());
    }
    else
    {
        sendCommand(user, 464, ERR_PASSWDMISMATCH());
    }

}