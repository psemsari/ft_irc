#include "Command.hpp"

void	Command::_motd(std::stringstream& completeCommand, User& user) {

    (void)completeCommand;
    std::string msg = MOTD;
    if (msg.empty() == true)
    {
        sendCommand(user, 422, ERR_NOMOTD());
        return;
    }
    std::string name = static_cast<std::string>(SERV_NAME);
    sendCommand(user, 375, RPL_MOTDSTART(name));
    sendCommand(user, 372, RPL_MOTD(msg));
    sendCommand(user, 376, RPL_ENDOFMOTD());
}
