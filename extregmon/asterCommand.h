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
	

	virtual std::string getStartSipLogCmd();
	virtual bool checkSipPacketBegin(std::string line);
	virtual bool checkSipPacketEnd(std::string line);
	virtual std::string formateDateTime(std::tm tm);
	virtual void scanErrorInLog(std::ifstream& log, std::string login, std::vector<string>& pt);
	virtual std::string getTimeFromPacketBegin(std::string);
	virtual bool checkSipIncomeCall(std::string line);
	virtual bool getTimeFromLine(std::string line, std::string& timestr);
	virtual std::string reloadLineCMD(std::string, std::string userId);
};

