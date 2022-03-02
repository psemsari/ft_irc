#include "Command.hpp"

void    Command::_quit(std::stringstream& completeCommand, User& user) {

    std::string arg;
    std::string reply;

    completeCommand >> arg;
    reply = "QUIT " + arg + "\r\n";
	send(user.getFd(), reply.c_str(), reply.size(), SEND_OPT);
    user.setIsEnded(true);
}
