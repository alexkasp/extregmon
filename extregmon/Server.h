#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>



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
};

