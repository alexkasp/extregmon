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
	// scan log file for log with this line
	virtual int getLineLog(string login, std::vector<std::string>& pt);
};

