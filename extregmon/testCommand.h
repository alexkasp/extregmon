#pragma once
#include "ICommand.h"
class testCommand :
	public ICommand
{
public:
	testCommand();
	virtual ~testCommand();
	// ovveride virtual int RunParse(const boost::property_tree::ptree& data) = 0;
	int RunParse(boost::property_tree::ptree& data);
	// check if line exists on server and find out status of registration
	int checkLineStatus(string login, boost::property_tree::ptree& data);
};

