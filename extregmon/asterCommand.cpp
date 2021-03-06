#include "asterCommand.h"



asterCommand::asterCommand()
{
}


asterCommand::~asterCommand()
{
}

bool asterCommand::getTimeFromLine(std::string line, std::string& timestr)
{
	timestr =  "00:00:00 01/01/1970";
	return false;
}


std::string asterCommand::getTimeFromPacketBegin(std::string)
{
	return "00:00:00 01/01/1970";
}

std::string asterCommand::reloadLineCMD(std::string, std::string userId)
{
	return "have to implement";
}

void asterCommand::scanErrorInLog(std::ifstream& log, std::string login, std::vector<string>& pt)
{

}

std::string asterCommand::getStartSipLogCmd()
{

	return "/usr/sbin/asterisk -rx \"sip set debug on\"";
}

std::string asterCommand::SayHello()
{
	return "Asterisk pbx build: 0.001";
}

std::string asterCommand::formateDateTime(std::tm tm)
{
	//[2017-06-22 13:56:53] example
	
	
	ostringstream os;
	os << "[20" << tm.tm_year-100 << "-" <<setfill('0')<<setw(2)<< tm.tm_mon+1 << "-" <<setfill('0')<<setw(2)<< tm.tm_mday << " " <<setfill('0')<<setw(2)<< tm.tm_hour << ":" <<setfill('0')<<setw(2)<< tm.tm_min << ":" <<setfill('0')<<setw(2)<< tm.tm_sec << "]";
	return os.str();

}

bool asterCommand::checkSipPacketBegin(std::string line)
{
	
	string SIGNATURE = "<--- SIP read from";
	if (line.compare(SIGNATURE) == 1)
	{
	    return true;
	}
	return false;
}

bool asterCommand::checkSipIncomeCall(std::string line)
{
    return false;
}

bool asterCommand::checkSipPacketEnd(std::string data)
{
	
	if ( (data.c_str()[1] == '<') && (data.c_str()[2] == '-') && 
		(data.c_str()[3] == '-') && (data.c_str()[4] == '-') && (data.c_str()[5] == '-') &&
		(data.c_str()[6] == '-') && (data.c_str()[7] == '-') && (data.c_str()[8] == '-') && (data.c_str()[9] == '-'))
		{
		    return true;
		}
		
	return false;
}

std::string asterCommand::getLineStatusCMD(std::string login)
{
	return "/usr/sbin/asterisk -rx \"sip show registry\"|grep "+login;
}

std::string  asterCommand::getLogFilename()
{
	return "/var/log/asterisk/full";

}