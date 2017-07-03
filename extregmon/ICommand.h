#pragma once
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
class ICommand
{
public:
	static const std::string RESULT_LABEL;
	ICommand();
	virtual ~ICommand();
	// Parse data and make action
	virtual int RunParse(boost::property_tree::ptree& data);
	// get output from command execution in shell
	string getConsoleOutput(string command);
	// report self type and additional data
	

	std::string getTimeStr(std::string requestTime);

	void startSipLogs();




	std::string checkLineStatus(string statusCMD);
	// scan log file for log with this line
	int getLineLog(string login, string reqtimestr,std::vector<std::string>& pt);

	int SetPositionToBeginSipHeader(std::ifstream& log, int&sendcounter);
	int SendSipPacket(std::ifstream& log, int sendcounter, std::vector<std::string>& pt);
	int LineBackLog(std::ifstream& log);

	virtual std::string getStartSipLogCmd();
	virtual std::string getLineStatusCMD(std::string login) = 0;
	virtual std::string getLogFilename() = 0;
	virtual bool checkSipPacketBegin(std::string line) = 0;
	virtual bool checkSipPacketEnd(std::string line) = 0;
	virtual std::string SayHello() = 0;
	virtual std::string formateDateTime(std::tm tm) = 0;
};

