#include "Server.h"
#include "testCommand.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


Server::Server()
{
}


Server::~Server()
{
}


// start listen for incomming commands
bool Server::startListen(int port)
{
	try
	{
		testCommand tc;
		tcp::acceptor acceptor(io_main, tcp::endpoint(tcp::v4(), 13));

		for (;;)
		{
			tcp::socket socket(io_main);
			acceptor.accept(socket);

			std::string message;
			boost::property_tree::ptree pt;

			boost::system::error_code ignored_error;

			boost::asio::streambuf input;

			boost::asio::read(socket, input,ignored_error);
			boost::property_tree::read_json(message, pt);
			
			tc.RunParse(pt);
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}

		return true;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return false;
}
