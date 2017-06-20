#include "Server.h"
#include "testCommand.h"
#include "asterCommand.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>

Server::Server()
{
}


Server::~Server()
{
}


// start listen for incomming commands
bool Server::startListen(int port)
{
		ICommand* tc = nullptr;
		tcp::acceptor acceptor(io_main, tcp::endpoint(tcp::v4(), port));

		for (;;)
		{
			try
			{
				tcp::socket socket(io_main);
				acceptor.accept(socket);
				boost::system::error_code ignored_error;

				int commandtype = getCommandType("/var/lib/asterisk/agi-bin/system_variables.php", "pbxtype");
				if (commandtype == 1)
					tc = new testCommand();
				else if (commandtype == 2)
					tc = new asterCommand();

				std::string message = tc->SayHello();
				boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		
				while(1)
				{
					MainLoop(socket, tc);
				}
			}
			catch (std::exception& e)
			{
			    std::cerr << e.what() << std::endl;
			}
		}

		return true;
	
	
}


// get CommandType from selected param in file
int Server::getCommandType(string filename, string paramname)
{
	std::ifstream ifile(filename);
	if (ifile.is_open())
	{
		char* value;
		char buf[512];
		char* param;
		while (ifile.getline(buf,512))
		{
			if ((param=strstr(buf, paramname.c_str())) != nullptr)
			{
				char * valuestr = strstr(param, "=");
				valuestr++; valuestr++;

				value = valuestr;
				value[strlen(valuestr) - 2] = 0;
				break;
			}

		}
		if (strcmp(value, "aster") == 0)
			return 1;
		else if (strcmp(value, "extreg") == 0)
			return 2;
	}
	return 0;
}


int Server::MainLoop(tcp::socket& socket, ICommand* module)
{
	std::string message = "";
	boost::property_tree::ptree pt;
	boost::system::error_code ignored_error;

	if(ParseToJson(socket, pt))
	{
		module->RunParse(pt);
		std::ostringstream oss;
		boost::property_tree::json_parser::write_json(oss, pt);
		message = oss.str();
		
		boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		return 1;
	}
	return 0;
}


int Server::ParseToJson(tcp::socket& socket, boost::property_tree::ptree& pt)
{
	std::stringstream ss;
	boost::asio::streambuf input;
	boost::system::error_code ignored_error;

	try
	{
		size_t size = boost::asio::read_until(socket, input, "\r\n", ignored_error);
		string str(boost::asio::buffers_begin(input.data()), boost::asio::buffers_begin(input.data()) + input.size());
		input.consume(size);
		ss << str;
		boost::property_tree::read_json(ss, pt);
		return 1;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
