#include "testCommand.h"
#include <iostream>


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
			string login = data.get<std::string>("LineStatusLogin", "");
			checkLineStatus(login,data);

		}
    }
      catch (std::exception &e)
          {
                  std::cout << "Error: " << e.what() << "\n";
                      }
	return 0;
}


// check if line exists on server and find out status of registration
int testCommand::checkLineStatus(string login, boost::property_tree::ptree& data)
{
	string output = getConsoleOutput("/etc/freeswitch/cli_args \'sofia status gateway\'|grep "+login);
	string msg = "extregTest:";

	msg+=" not found";
	std::cout<<"checkLine send\n";
	string checkfield = data.get("checkLineStatus","");
	if(checkfield.empty())
	    data.put("checkLineStatus", msg);
	else
	    data.add("checkLineStatus", msg);

	msg+=" external::18136325029             sip:410997@sip.zadarma.com        REGED     0.00  0/1     1/1";
	data.add("checkLineStatus", msg);

	return 0;
}
