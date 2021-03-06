#pragma once
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
class ICommand
{
	static const int LINELENGTH;

	int setLogOnTime(ifstream& log, string reqtimestr);
	void reportList(vector<string>& readdata,boost::property_tree::ptree& data,string noanswer);
	void getCallData(std::ifstream& log,std::string& numFrom,std::string& callId);
	std::string getChannel(std::ifstream& log,std::string numFrom,std::string& channelDescr);
	void getCallLog(std::string channel, vector<string>& readdata);
	
	
	void getCallPartial(string channel,ifstream& log,vector<string>& readdata);
	
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

	std::string startSipLogs();




	std::string checkLineStatus(string statusCMD);
	// scan log file for log with this line
	int getLineLog(string login, string reqtimestr,std::vector<std::string>& pt);

	int SetPositionToBeginSipHeader(std::ifstream& log, int&sendcounter);
	int SendSipPacket(std::ifstream& log, int sendcounter, std::vector<std::string>& pt);
	void lookForError(string login, string reqtimestr, vector<string>& readdata);
	int LineBackLog(std::ifstream& log);
	std::string getPrevTime(ifstream& log);
	std::string getNextTime(ifstream& log);
	size_t getCallLogPartial(string channel, string reqtimestr, vector<string>& readdata, std::ifstream& log);
	size_t getCallLogPartial(string channel, size_t position, vector<string>& readdata, std::ifstream& log);

	virtual std::string getStartSipLogCmd();
	virtual std::string getLineStatusCMD(std::string login) = 0;
	virtual std::string getLogFilename() = 0;
	virtual bool checkSipPacketBegin(std::string line) = 0;
	virtual bool checkSipPacketEnd(std::string line) = 0;
	virtual bool checkSipIncomeCall(std::string line) = 0;
	virtual std::string SayHello() = 0;
	virtual std::string formateDateTime(std::tm tm) = 0;
	virtual bool getIncomeCallList(std::string login,vector<string>& list);
	virtual void scanErrorInLog(std::ifstream& log, std::string login, std::vector<string>& pt) = 0;
	virtual std::string getTimeFromPacketBegin(std::string) = 0;
	virtual bool getTimeFromLine(std::string line,std::string& timestr) = 0;
	virtual std::string reloadLineCMD(std::string, std::string userId) = 0;

};

