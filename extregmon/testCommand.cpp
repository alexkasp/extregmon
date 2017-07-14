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
	if ((data.find(STARTPACKETSIGNATURE1)!= string::npos) ||
		(data.find(STARTPACKETSIGNATURE2) != string::npos) ||
		(data.find(STARTPACKETSIGNATURE3) != string::npos) || (data.find(STARTPACKETSIGNATURE4) != string::npos))
		return true;
		
	return false;
}
bool testCommand::checkSipPacketEnd(std::string data)
{
	if ((data.c_str()[3] == '-') && (data.c_str()[4] == '-') && (data.c_str()[5] == '-') && (data.c_str()[6] == '-') && (data.c_str()[7] == '-') && (data.c_str()[8] == '-') && (data.c_str()[9] == '-'))
		return true;
	return false;
}



void testCommand::scanErrorInLog(std::ifstream& log, std::string login, std::vector<string>& pt)
{
	DnsError(log, login, pt);
}

void testCommand::DnsError(std::ifstream& log, std::string login, std::vector<string>& pt)
{
	auto position = log.tellg();
	const int buflength = 10000;
	char data[buflength];

	const std::string label = "Failed Registration with status DNS Error";
	const std::string errorDescription = "DNS error - can not resolve hostname";

	while (log.getline(data, buflength))
	{
		if(login.find(data)!= string::npos)
			if (label.find(data) != string::npos)
			{
				pt.push_back(errorDescription);
				pt.push_back(data);
				break;
			}

	}

	log.seekg(position, SEEK_CUR);

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