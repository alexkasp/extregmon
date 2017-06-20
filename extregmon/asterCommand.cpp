#include "asterCommand.h"



asterCommand::asterCommand()
{
}


asterCommand::~asterCommand()
{
}


std::string asterCommand::SayHello()
{
	return "Asterisk pbx build: 0.001";
}


// scan log file for log with this line
int asterCommand::getLineLog(string login, std::vector<std::string>& pt)
{
	return 0;
}

std::string asterCommand::getLineStatusCMD(std::string login)
{
	return "/uisr/sbin/asterisk -rx \"sip show registry\"|grep"+login;
}