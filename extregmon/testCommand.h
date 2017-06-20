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
	// check if line exists on server and find out status of registration
	virtual std::string getLineStatusCMD(std::string login);
	// scan log file for log with this line
	virtual int getLineLog(string login, std::vector<std::string>& pt);
	// set position one line back
	int LineBackLog(std::ifstream& log);
	// set read ptr to start sip packet
	int SetPositionToBeginSipHeader(std::ifstream& log, int&sendcounter);
	int SendSipPacket(std::ifstream& log, int sendcounter, std::vector<std::string>& pt);
	virtual std::string SayHello();
};

