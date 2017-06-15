#pragma once
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
class ICommand
{
public:
	ICommand();
	virtual ~ICommand();
	// Parse data and make action
	virtual int RunParse(boost::property_tree::ptree& data) = 0;
};

