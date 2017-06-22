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
				string output = checkLineStatus(statusCMD);
				data.put("LineStatus", output);
				return 1;
			}
			if (command.compare("GetSipLogs") == 0)
			{
				string login = data.get<std::string>("LineSipLogLogin", "");
				vector<string> readdata;
				getLineLog(login, readdata);
				data.add("log", "Start Log");
				for (auto x = readdata.begin(); x != readdata.end(); ++x)
					data.add("log", (*x));
				data.add("log", "End Log");
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