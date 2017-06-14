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
		testCommand tc;
		tcp::acceptor acceptor(io_main, tcp::endpoint(tcp::v4(), port));

		for (;;)
		{
			try
			{
			std::stringstream ss;
			
			std::cout<<"Start execution...\n";
			tcp::socket socket(io_main);
			acceptor.accept(socket);
			
			std::cout<<"connection accepted\n";
			
			
			boost::property_tree::ptree pt;

			boost::asio::streambuf input;
			boost::system::error_code ignored_error;

			
			std::string message = "{\"help\":\"Send json!!!\"}";
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
			 
			while(1)
			{
			    size_t size = boost::asio::read_until(socket, input,"\r\n",ignored_error);
			
			    string str(boost::asio::buffers_begin(input.data()), boost::asio::buffers_begin(input.data()) + input.size());
			    input.consume(size);
			    std::cout<<"read data \n"<<str<<"\n";
			
			    ss<<str;
			
			    boost::property_tree::read_json(ss, pt);
			
			    std::cout<<"run parse\n";
			
			    tc.RunParse(pt);
			    message = "{\"help\":\"ready for new command\"}";
			    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
			}
			}
			catch (std::exception& e)
			{
			    std::cerr << e.what() << std::endl;
			}
		}

		return true;
	
	
}
