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

	void DnsError(std::ifstream& log, std::string login, std::vector<string>& pt);
	
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
	virtual void scanErrorInLog(std::ifstream& log, std::string login,std::vector<string>& pt);
	virtual std::string getTimeFromPacketBegin(std::string);
	virtual bool checkSipIncomeCall(std::string line);
	virtual bool getTimeFromLine(std::string line, std::string& timestr);
	virtual std::string reloadLineCMD(std::string login, std::string userId);
};

