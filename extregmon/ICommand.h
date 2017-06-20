#pragma once
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
class ICommand
{
public:
	ICommand();
	virtual ~ICommand();
	// Parse data and make action
	virtual int RunParse(boost::property_tree::ptree& data);
	// get output from command execution in shell
	string getConsoleOutput(string command);
	// report self type and additional data
	virtual std::string SayHello() = 0;
	

	std::string checkLineStatus(string statusCMD);
	// scan log file for log with this line
	virtual int getLineLog(string login, std::vector<std::string>& pt) = 0;
	virtual std::string getLineStatusCMD(std::string login) = 0;


};

