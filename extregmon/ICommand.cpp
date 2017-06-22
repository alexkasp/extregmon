#include "ICommand.h"
#include <iostream>
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




// get output from command execution in shell
string ICommand::getConsoleOutput(string command)
{
	const int MaxOutput = 12550;
	char output[MaxOutput];
	string resultoutput = "";
#ifdef __linux__
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
				vector<string> readdata;
				getLineLog(login, readdata);
				if(readdata.size()>0)
				{
				    for (auto x = readdata.begin(); x != readdata.end(); ++x)
					    data.add(ICommand::RESULT_LABEL+".log", (*x));
				}
				else
				    data.add(ICommand::RESULT_LABEL+".log","NOT FOUND LOGS");
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

std::string ICommand::checkLineStatus(std::string statusCMD)
{
	
	string output = getConsoleOutput(statusCMD);
	string msg = "extregTest:";
	msg += output;

	return output;
}

int ICommand::getLineLog(string login, std::vector<std::string>& pt)
{
	ifstream log(getLogFilename());
	int i = 0;
	if (log)
	{
		char data[10000];
		std::streamoff ptr;
		ptr = log.tellg();
		while (log.getline(data, 8096))
		{

			if (strstr(data, login.c_str()))
			{

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


	}
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