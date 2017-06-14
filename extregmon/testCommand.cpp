#include "testCommand.h"
#include <iostream>


testCommand::testCommand()
{
}


testCommand::~testCommand()
{
}


// ovveride virtual int RunParse(const boost::property_tree::ptree& data) = 0;
int testCommand::RunParse(const boost::property_tree::ptree& data)
{
    try
    {
	std::cout<<"try parse json\n";
	string msg = data.get<std::string>("test");
	std::cout << msg << "\n";
    }
      catch (std::exception &e)
          {
                  std::cout << "Error: " << e.what() << "\n";
                      }
	return 0;
}
