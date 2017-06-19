#include "testCommand.h"
#include <iostream>
#include <fstream>


testCommand::testCommand()
{
}


testCommand::~testCommand()
{
}


// ovveride virtual int RunParse(const boost::property_tree::ptree& data) = 0;
int testCommand::RunParse(boost::property_tree::ptree& data)
{
    try
    {
		std::cout<<"try parse json\n";
		string msg = data.get<std::string>("test","");
		if(!msg.empty())
			std::cout << msg << "\n";
		string command = data.get<std::string>("Command", "");
		if (!command.empty())
		{
		    if(command.compare("LineStatus")==0)
		    {
			string login = data.get<std::string>("LineStatusLogin", "");
			checkLineStatus(login,data);
			return 1;
		    }
		    if(command.compare("GetSipLogs")==0)
		    {
			string login = data.get<std::string>("LineSipLogLogin","");
			vector<string> readdata;
			getLineLog(login,readdata);
			for(auto x = readdata.begin();x!=readdata.end();++x)
			    data.add("log",(*x));
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


// check if line exists on server and find out status of registration
int testCommand::checkLineStatus(string login, boost::property_tree::ptree& data)
{
//	string output = getConsoleOutput("/etc/freeswitch/cli_args \'sofia status gateway\'|grep "+login);
	string output = getConsoleOutput("cat ./test.out|grep "+login);
	string msg = "extregTest:";

/*	msg+=" not found";
	std::cout<<"checkLine send\n";
	string checkfield = data.get("checkLineStatus","");
	if(checkfield.empty())
	    data.put("checkLineStatus", msg);
	else
	    data.add("checkLineStatus", msg);
*/
	msg+=output;//" external::18136325029             sip:410997@sip.zadarma.com        REGED     0.00  0/1     1/1";
	data.put("checkLineStatus", msg);

	return 0;
}


// scan log file for log with this line
int testCommand::getLineLog(string login, std::vector<std::string>& pt)
{
//	ifstream log("/var/log/freeswitch/freeswitch.log");
	ifstream log("./test.log");
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
			    std::cout<<"FIND "<<data<<"\n";
			    
			    if(strstr(data, "From:"))
				{
				
				//	if ((data[3] == '-')&& (data[4] == '-') && (data[5] == '-') && (data[6] == '-') && (data[7] == '-') && (data[8] == '-') && (data[9] == '-') )
					//	continue;
				    int sendcounter = 0;
				    if (SetPositionToBeginSipHeader(log,sendcounter))
					SendSipPacket(log,sendcounter,pt);
				    else
				    {
					break;
				    }
				}
			}
			if(log.eof())
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


// set position one line back
int testCommand::LineBackLog(std::ifstream& log)
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
int testCommand::SetPositionToBeginSipHeader(std::ifstream& log, int&sendcounter)
{
	int i=0;
	char data[8096];
	while (true)
	{
		++i;
		
		int prevlineback = LineBackLog(log);
		if(!LineBackLog(log)||!prevlineback)
		{
		    std::cout<<"Error line back\n";
		    return 0;
		}
		std::cout << "SetPosition" << std::endl;
		log.getline(data, 8096);
		
		if (strstr(data, STARTPACKETSIGNATURE1.c_str()) || 
			strstr(data, STARTPACKETSIGNATURE2.c_str()) || 
			strstr(data, STARTPACKETSIGNATURE3.c_str()) || strstr(data, STARTPACKETSIGNATURE4.c_str())|| 
			((data[3] == '-') && (data[4] == '-') && (data[5] == '-') && (data[6] == '-') && (data[7] == '-') && (data[8] == '-') && (data[9] == '-')))
		{
			std::cout<<"WE FINK WE ON START PACKET\n";
			LineBackLog(log);
			return 1;
		}
		if(log.eof())
		    return 1;
	}

	return 0;
}


int testCommand::SendSipPacket(std::ifstream& log, int sendcounter, std::vector<std::string>& pt)
{
	std::cout<<"THIS LINES ADD TO TREE\n";
	
	char packetdata[8096];
	char data[8096];
	log.getline(packetdata, 8096);
	log.getline(packetdata, 8096);
	pt.push_back(packetdata);
		std::cout<<"THIS LINES ADD TO TREE\n"<<packetdata<<"\n";
	while (log.getline(data, 8096))
	{
		if (strstr(data, STARTPACKETSIGNATURE1.c_str()) ||
			strstr(data, STARTPACKETSIGNATURE2.c_str()) ||
			strstr(data, STARTPACKETSIGNATURE3.c_str()) || strstr(data, STARTPACKETSIGNATURE4.c_str()) ||
			((data[3] == '-') && (data[4] == '-') && (data[5] == '-') && (data[6] == '-') && (data[7] == '-') && (data[8] == '-') && (data[9] == '-')))
		{
			std::cout<<"WE FINISH READ PACKET - GO SEARCH AGAIN\n";
			return 1;
		}
		--sendcounter;
		
		std::cout<<data<<"\n";
		pt.push_back(data);

	}

	if(log.eof())
	    return 1;
	return 0;
}
