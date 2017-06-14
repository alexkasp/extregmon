#pragma once
#include "ICommand.h"
class testCommand :
	public ICommand
{
public:
	testCommand();
	virtual ~testCommand();
	// ovveride virtual int RunParse(const boost::property_tree::ptree& data) = 0;
	int RunParse(const boost::property_tree::ptree& data);
};

