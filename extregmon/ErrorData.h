#pragma once

#include <string>

class ErrorData
{
	std::string calluniqueid;

public:

	static bool getStartCall(std::string line);
	virtual bool curPBXCallStart(std::string line) = 0;
	virtual bool getEndCall(std::string call, std::string line);


	ErrorData();
	virtual ~ErrorData();
};

