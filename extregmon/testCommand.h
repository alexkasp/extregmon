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

	virtual bool checkSipPacketBegin(std::string line);
	virtual bool checkSipPacketEnd(std::string line);

	virtual std::string SayHello();
	virtual std::string getLogFilename();
	virtual std::string formateDateTime(std::tm tm);
};

