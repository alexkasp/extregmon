#include "MainListen.h"
#include "Server.h"
#include <boost/regex.hpp>

int main()
{
boost::regex expression("(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}.\\d{2,6})");
boost::regex expression1("(\\d+)");
std::string log = "6c0c0fae-78d6-11e7-b09d-0177bd11a386 2017-08-04 08:33:18.922637 [DEBUG] sofia.c:9248 sofia/internal/70287802@sip.nsk.mcn.ru receiving invite from 212.193.100.169:5060 version: 1.6.6  64bit2";
 boost::smatch what;
 
 std::string::const_iterator xItStart = log.begin();
 std::string::const_iterator xItEnd = log.end();
 
 if(regex_search(xItStart,xItEnd,what,expression))
 {
    std::cout<<what[0]<<"\n";
    std::cout<<what[1]<<"\n";
    
 }
	Server srv;
	    srv.startListen(7524);
	return 0;
}