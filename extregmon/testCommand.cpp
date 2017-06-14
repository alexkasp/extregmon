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
	string msg = data.get<std::string>("test");
	std::cout << msg << "\n";
	return 0;
}
