#include "testCommand.h"
#include <iostream>
#include <fstream>


testCommand::testCommand()
{
}


testCommand::~testCommand()
{
}


std::string testCommand::getLineStatusCMD(std::string login)
{

	return "/etc/freeswitch/cli_args \'sofia status gateway\'|grep " + login;
}

// scan log file for log with this line



bool testCommand::checkSipPacketBegin(std::string data)
{
	if ((data.compare(STARTPACKETSIGNATURE1) == 0) ||
		(data.compare(STARTPACKETSIGNATURE2) == 0) ||
		(data.compare(STARTPACKETSIGNATURE3) == 0) || (data.compare(STARTPACKETSIGNATURE4) == 0))
		return true;
		
	return false;
}
bool testCommand::checkSipPacketEnd(std::string data)
{
	if ((data.c_str()[3] == '-') && (data.c_str()[4] == '-') && (data.c_str()[5] == '-') && (data.c_str()[6] == '-') && (data.c_str()[7] == '-') && (data.c_str()[8] == '-') && (data.c_str()[9] == '-'))
		return true;
	return false;
}





std::string testCommand::SayHello()
{
	return "FreeSwitch pbx build: 0.001";
}

std::string testCommand::getLogFilename()
{

	return "/var/log/freeswitch/freeswitch.log";
}

std::string testCommand::formateDateTime(std::tm tm)
{
	//2017-06-22 16:08:23 example
	ostringstream os;
	os << tm.tm_year << "-" << tm.tm_mon << "-" << tm.tm_mday << " " << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec;
	return os.str();
}