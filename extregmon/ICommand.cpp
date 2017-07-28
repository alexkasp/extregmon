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

void ICommand::getCallData(std::ifstream& log,std::string& numFrom,std::string& callId)
{
    const int linelength = 10000;
    char buf[linelength];
    
    const std::string fromField = "From: ";
    const std::string callIdField = "Call-ID:";
    const std::string numBegin = "<sip:";
    const std::string numEnd = "@";
    const std::string callIdBegin = callIdField;
    const std::string callIdEnd = "@";

    while (log.getline(buf, linelength))
    {
	    string datastr = buf;
	    if (datastr.find(fromField) != string::npos)
	    {
			std::cout<<"FROM FIELD\n"<<datastr<<"\n";
			auto numBeginPosition = datastr.find(numBegin) + numBegin.length();
			auto numEndPosition = datastr.find(numEnd);
	
			numFrom  = datastr.substr(numBeginPosition, numEndPosition - numBeginPosition);
			std::cout<<numFrom<<"\n";
			
	    }
	    else if (datastr.find(callIdField) != string::npos)
	    {
			std::cout<<"CALLID FIELD\n"<<datastr<<"\n";
			
			auto callIdBeginPosition = datastr.find(callIdBegin) + callIdBegin.length();
			auto callIdEndPosition = datastr.find(callIdEnd);

			callId  = datastr.substr(callIdBeginPosition, callIdEndPosition - callIdBeginPosition);
			std::cout<<callId<<"\n";
			
	    }
			    
	    if((!numFrom.empty())&&(!callId.empty()))
	        break;
    }	
    
    
    return;
}

std::string ICommand::getChannel(std::ifstream& log,std::string numFrom,std::string& channelDescr)
{
    const std::string prefixchannelNewSignature = "New Channel ";
    const std::string channelNewSignature = "sofia/external/";
    const std::string channelFullSignature = prefixchannelNewSignature+channelNewSignature+numFrom;
    const std::string channelDomainSignature = "@";
    const std::string channelNameSignature = "[";
    
    const int linelength = 10000;
    std::string datastr = "";
    char buf[linelength];
    
    while(log.getline(buf,linelength))
    {
	datastr = buf;
	auto channelFullNamePosition = datastr.find(channelFullSignature);
	if(channelFullNamePosition!=string::npos)
	{
	    auto channelNamePosition = datastr.find(channelNewSignature);
	    string parseStr = datastr.substr(channelNamePosition);
	    
	    auto channelSignaturePosition = parseStr.find(channelNameSignature);
	    if(channelSignaturePosition!=string::npos)
	    {
		string channelSignature = parseStr.substr(channelSignaturePosition+1,parseStr.length()-channelSignaturePosition-2);
		channelDescr = parseStr.substr(0,parseStr.length()-channelSignaturePosition-1);
		std::cout<<" channelDescr "<<channelDescr<<"  "<<channelSignaturePosition<<"  "<<parseStr.length()<<"\n";
		return channelSignature;
	    }
	}
    }
}

bool ICommand::getIncomeCallList(std::string login,vector<string>& list)
{
	ifstream log;
	log.open(getLogFilename());
	const int linelength = 10000;
	const std::string callBeginStrAny = "INVITE sip:";
	const std::string callBeginStr = "INVITE sip:"+login;

	char buf[linelength];
	std::cout<<"CallBeginStr = "<<callBeginStr<<"\n";
	
	while (log.getline(buf,linelength))
	{
		string datastr = buf;
		if ((checkSipPacketBegin(datastr))&&(checkSipIncomeCall(datastr)))
		{
			std::string callTime = getTimeFromPacketBegin(datastr);
			std::cout<<datastr<<"\n";
			log.getline(buf,linelength);
			
			while (log.getline(buf,linelength))
			{
			    string numFrom="";
			    string callId="";
			
			    datastr = buf;
			    if(datastr.find(callBeginStr)!=string::npos)
			    {
				
					string channelDescr = "";
					string channelSignature = "";
				
					getCallData(log,numFrom,callId);	
					channelSignature = getChannel(log,numFrom,channelDescr);
					string reportLine = callTime + " " + login + " " + numFrom + " "+callId+" descr = ["+channelDescr+"] signature = ["+channelSignature+"]";
					std::cout<<"\n"<<reportLine<<"\n";
					list.push_back(reportLine);
					break;
			    }
			    else if(datastr.find(callBeginStrAny)!=string::npos)
					break;
			    else if(checkSipPacketEnd(datastr))
					break;
			}    
		}
	}

	log.close();
    return true;
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
			if (command.compare("getCalls") == 0)
			{
				string login = data.get<std::string>("LineSipLogLogin", "");

				vector<string> readdata;

				std::cout << "ErrorSearch start\n";
				getIncomeCallList(login, readdata);

				reportList(readdata, data, "NOT CALLS FOUND");

				return 1;
			}
			if (command.compare("getCallLogFull") == 0)
			{
				string channel = data.get<std::string>("ChannelSignature", "");

				vector<string> readdata;

				std::cout << "getCallLogFull start\n";
				getCallLog(channel, readdata);

				reportList(readdata, data, "NOT CALLS FOUND");

				return 1;
			}
			if (command.compare("getCallLogPartial") == 0)
			{
				string channel = data.get<std::string>("ChannelSignature", "");
				string reqtimestr = data.get<std::string>("RequestTime", "");

				vector<string> readdata;

				std::cout << "getCallLogPartial start\n";
				size_t position = getCallLogPartial(channel,reqtimestr, readdata);

				reportList(readdata, data, "NOT CALLS FOUND");
				
				data.add(ICommand::RESULT_LABEL+".log",position);
				return 1;
			}
			if (command.compare("getCallLogPartialPosition") == 0)
			{
				string channel = data.get<std::string>("ChannelSignature", "");
				size_t position = data.get<std::size_t>("RequestTime", 0);

				vector<string> readdata;

				std::cout << "getCallLogPartial start\n";
				size_t newposition = getCallLogPartial(channel,position, readdata);

				reportList(readdata, data, "NOT CALLS FOUND");
				
				data.add(ICommand::RESULT_LABEL+".log",newposition);
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
size_t ICommand::getCallLogPartial(string channel, string reqtimestr, vector<string>& readdata)
{
	ifstream log;
	log.open(getLogFilename());
	
	std::cout<<"getCallLogPartial channel = "<<channel<<" reqtimestr = "<<reqtimestr<<"\n";
	
	const int linelength = 10000;
	char buf[linelength];

	while (log.getline(buf, linelength))
	{
		string datastr = buf;
		
		if (datastr.find(reqtimestr) != string::npos)
		{
			LineBackLog(log);
			getCallPartial(channel,log,readdata);
			break;
		}

	}
	size_t curPosition = log.tellg();
	log.close();
	return curPosition;

}

size_t ICommand::getCallLogPartial(string channel, size_t position, vector<string>& readdata)
{
	ifstream log;
	log.open(getLogFilename());
	
	const int linelength = 10000;
	char buf[linelength];

	log.seekg(position);
	
	string datastr = buf;
	getCallPartial(channel,log,readdata);

	
	
	size_t curPosition = log.tellg();
	log.close();
	return curPosition;

}

void ICommand::getCallPartial(string channel,ifstream& log,vector<string>& readdata)
{
    int readmode = 0;
    const int linelength = 10000;
    char buf[linelength];

    std::cout<<"Partial - search for call log\n";
    string datastr="";
    int i = 0;
    
    while (log.getline(buf, linelength))
    {
	datastr = buf;
	if(i++<10)
	    std::cout<<datastr<<"\n";
	
	if (datastr.find(channel) != string::npos)
	{
	    if(i++<10)
		std::cout<<"["<<datastr<<"]\n";
	    readmode = 1;
	    readdata.push_back(datastr);
	}
	else if (readmode)
	    break;

	}
	
	return;
}

void ICommand::getCallLog(std::string channel, vector<string>& readdata)
{
	ifstream log;
	log.open(getLogFilename());

	const int linelength = 10000;
	char buf[linelength];

	while (log.getline(buf,linelength))
	{ 
		string datastr = buf;

		if (datastr.find(channel) != string::npos)
			readdata.push_back(datastr);
	}

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
		std::string callTime="";
		while (log.getline(data, 8096))
		{
			
			if(checkSipPacketBegin(data))
			{
			    std::cout<<"get Time from "<<data<<"\n";
			     callTime = getTimeFromPacketBegin(data);
			     std::cout<<"Time is "<<callTime<<"\n";
			}
			if (strstr(data, login.c_str()))
			{
				std::cout<<"We find line\n"<<data<<"\n";

				if ((strstr(data, "From:"))||(strstr(data, "Call-ID:")))
				{

					int sendcounter = 0;
					if (SetPositionToBeginSipHeader(log, sendcounter))
					{
						
						
						pt.push_back("event time: "+callTime);
						
						std::cout<<"SendSipPacket\n";
						SendSipPacket(log, sendcounter, pt);
					}
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

		std::cout<<"[ "<<data<<"]\n";
		if((this->checkSipPacketEnd(data)))
		{
			std::cout<<"END PACKET\n";
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
