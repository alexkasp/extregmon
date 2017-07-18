#include "ICommand.h"
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <locale>

#ifdef __linux__
#include <stdio.h>

#endif // __linux__



ICommand::ICommand()
{
}


ICommand::~ICommand()
{
}

const std::string ICommand::RESULT_LABEL = "result";


bool ICommand::getIncomeCallList(std::string login,vector<string>& list)
{
    return false;
}

// get output from command execution in shell
string ICommand::getConsoleOutput(string command)
{
	
	string resultoutput = "";
#ifdef __linux__
	const int MaxOutput = 12550;
	char output[MaxOutput];
	FILE* stream = popen(command.c_str(), "r");
	while(fgets(output, 1024, stream)!=NULL)
	{
	    resultoutput += std::string(output);
	}

	pclose(stream);
#endif // __LINUX__

	


	return resultoutput;
}

int ICommand::RunParse(boost::property_tree::ptree& data)
{
	try
	{
		string command = data.get<std::string>("Command", "");
		std::cout<<"RunParse "<<command<<"\n";
		if (!command.empty())
		{
			if (command.compare("LineStatus") == 0)
			{
				string login = data.get<std::string>("LineStatusLogin", "");
				string statusCMD = getLineStatusCMD(login);
				std::cout<<"StatusCMD = "<<statusCMD<<"\n";
				string output = checkLineStatus(statusCMD);
				data.put(ICommand::RESULT_LABEL+".status", output);
				return 1;
			}
			if (command.compare("GetSipLogs") == 0)
			{
				string login = data.get<std::string>("LineSipLogLogin", "");
				string reqtimestr = data.get<std::string>("RequestTime", "");
				
				std::cout<<"GetSIPLOG for "<<login<<" from ["<<reqtimestr<<"]\n";
				
				vector<string> readdata;

				getLineLog(login, reqtimestr,readdata);
				reportList(readdata,data,"NOT FOUND LOGS");
				return 1;
			}
			if (command.compare("StartSipLogs") == 0)
			{
				data.put(ICommand::RESULT_LABEL+".siplog",startSipLogs());
				return 1;
			}
			if (command.compare("ErrorSearch") == 0)
			{
				string login = data.get<std::string>("LineSipLogLogin", "");
				string reqtimestr = data.get<std::string>("RequestTime", "");

				vector<string> readdata;

				std::cout<<"ErrorSearch start\n";
				lookForError(login, reqtimestr,readdata);
				
				reportList(readdata,data,"NOT FOUND ERRORS");
				
				return 1;
			}

		}
	}
	catch (std::exception &e)
	{
		std::cout << "Error from RunParse: " << e.what() << "\n";
	}
	return 0;
}


void ICommand::reportList(vector<string>& readdata,boost::property_tree::ptree& data,string noanswer)
{
    if(readdata.size()>0)
    {
        for (auto x = readdata.begin(); x != readdata.end(); ++x)
        {
    		std::cout<<"Add to ptree: \n"<<(*x)<<"\n";
		data.add(ICommand::RESULT_LABEL + ".log", (*x));
	}	
    }
    else
        data.add(ICommand::RESULT_LABEL+".log",noanswer);
}



void ICommand::lookForError(string login, string reqtimestr, vector<string>& readdata)
{
	ifstream log;
	setLogOnTime(log, reqtimestr);

	scanErrorInLog(log, login,readdata);
}

std::string ICommand::getStartSipLogCmd()
{
	return "";
}
std::string ICommand::startSipLogs()
{
	std::string CMD = getStartSipLogCmd();

	return getConsoleOutput(CMD);
}

std::string ICommand::checkLineStatus(std::string statusCMD)
{
	
	string output = getConsoleOutput(statusCMD);
	string msg = "extregTest:";
	msg += output;

	return output;
}

int ICommand::setLogOnTime(ifstream& log, string reqtimestr)
{
	log.open(getLogFilename());

	std::string timestr = getTimeStr(reqtimestr);
	std::cout<<"THIS TIME STR "<<timestr<<"\n";
	int i = 0;
	if (log)
	{
		char data[10000];
		std::streamoff ptr;
		ptr = log.tellg();
		if (!timestr.empty())
		{
			while (log.getline(data, 8096))
			{
				if (strstr(data, timestr.c_str()) != nullptr)
				{
					break;
				}	
					return 1;
			}
		}
		return 0;
	}
}

int ICommand::getLineLog(string login, string reqtimestr, std::vector<std::string>& pt)
{
		ifstream log;
		if (setLogOnTime(log, reqtimestr) == 0)
			return 0;
		
		char data[10000];

		while (log.getline(data, 8096))
		{

			if (strstr(data, login.c_str()))
			{
				std::cout<<"We find line\n"<<data<<"\n";

				if (strstr(data, "From:"))
				{

					int sendcounter = 0;
					if (SetPositionToBeginSipHeader(log, sendcounter))
						SendSipPacket(log, sendcounter, pt);
					else
					{
						break;
					}
				}
			}
			if (log.eof())
			{
				log.close();
				log.clear();

				return 1;
			}
		}
		log.close();
		log.clear();


	
	return 0;
}

int ICommand::SendSipPacket(std::ifstream& log, int sendcounter, std::vector<std::string>& pt)
{

	char packetdata[8096];
	char data[8096];
	log.getline(packetdata, 8096);
	log.getline(packetdata, 8096);
	pt.push_back(packetdata);
	while (log.getline(data, 8096))
	{


		if((this->checkSipPacketEnd(data)))
		{
			return 1;
		}
		--sendcounter;

		pt.push_back(data);

	}

	if (log.eof())
		return 1;
	return 0;
}

// set position one line back
int ICommand::LineBackLog(std::ifstream& log)
{
	log.seekg(-2, log.cur);
	while (true)
	{
		log.seekg(-2, log.cur);
		auto ptr = log.tellg();
		if (ptr < 0) return 0;
		char in = log.get();
		if (in == '\n')
			return 1;
	}

	return 0;
}


// set read ptr to start sip packet
int ICommand::SetPositionToBeginSipHeader(std::ifstream& log, int& sendcounter)
{
	int i = 0;
	char data[8096];
	while (true)
	{
		++i;

		int prevlineback = LineBackLog(log);
		if (!LineBackLog(log) || !prevlineback)
		{
			std::cout << "Error line back\n";
			return 0;
		}
		log.getline(data, 8096);

		if(this->checkSipPacketBegin(data))
		{
			LineBackLog(log);
			return 1;
		}
		if (log.eof())
			return 1;
	}

	return 0;
}

std::string ICommand::getTimeStr(std::string requestTime)
{
/*
	struct std::tm tm;
	std::istringstream ss(requestTime);

	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S"); // or just %T in this case
*/
	std::cout<<"getTimeStr\n";
	boost::posix_time::ptime pt(boost::posix_time::time_from_string(requestTime));
	std::cout<<"get ptime from string\n";
	std::tm tm  =  boost::posix_time::to_tm(pt);
	std::cout<<"convert ptime to tm\n";
	return formateDateTime(tm);
}
