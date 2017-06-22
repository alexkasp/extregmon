#pragma once
#include "ICommand.h"
class asterCommand :
	public ICommand
{
public:
	asterCommand();
	virtual ~asterCommand();
	std::string SayHello();
	virtual std::string getLineStatusCMD(std::string login);
	virtual std::string getLogFilename();
	

	virtual bool checkSipPacketBegin(std::string line);
	virtual bool checkSipPacketEnd(std::string line);
};

