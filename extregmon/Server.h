#ifndef SERVER_EXTREGMON
#define SERVER_EXTREGMON 1
#define BOOST_LIB_DIAGNOSTIC
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include "ICommand.h"



using boost::asio::ip::tcp;

class Server
{
public:
	Server();
	virtual ~Server();
	// start listen for incomming commands
	bool startListen(int port);
protected:
	// main io object
	boost::asio::io_service io_main;
public:
	// get CommandType from selected param in file
	int getCommandType(std::string filename, std::string paramname);
	int MainLoop(tcp::socket& socket, ICommand* module);
	int ParseToJson(tcp::socket& socket, boost::property_tree::ptree& pt);
};


	
#endif