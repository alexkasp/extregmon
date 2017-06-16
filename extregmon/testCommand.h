#pragma once
#include "ICommand.h"
#include <vector>

class testCommand :
	public ICommand
{
	string STARTPACKETSIGNATURE1 = "bytes to udp/";
	string STARTPACKETSIGNATURE2 = "bytes from udp/";
	string STARTPACKETSIGNATURE3 = "bytes to tcp/";
	string STARTPACKETSIGNATURE4 = "bytes from tcp/";
public:
	testCommand();
	virtual ~testCommand();
	// ovveride virtual int RunParse(const boost::property_tree::ptree& data) = 0;
	int RunParse(boost::property_tree::ptree& data);
	// check if line exists on server and find out status of registration
	int checkLineStatus(string login, boost::property_tree::ptree& data);
	// scan log file for log with this line
	int getLineLog(string login, std::vector<std::string>& pt);
	// set position one line back
	int LineBackLog(std::ifstream& log);
	// set read ptr to start sip packet
	int SetPositionToBeginSipHeader(std::ifstream& log, int&sendcounter);
	int SendSipPacket(std::ifstream& log, int sendcounter, std::vector<std::string>& pt);
};

