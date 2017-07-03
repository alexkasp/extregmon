#include "Server.h"
#include "testCommand.h"
#include "asterCommand.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <fstream>

#define ASTER_PBX_DETECTED 1
#define FREESWITCH_PBX_DETECTED 2



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
		
		int commandtype = getCommandType("/var/lib/asterisk/agi-bin/system_variables.php", "pbxtype");
		if (commandtype == FREESWITCH_PBX_DETECTED)
		{
		    tc = new testCommand();
		    std::cout<<"create freeswitch module\n";
		}
		else if (commandtype == ASTER_PBX_DETECTED)
		{
		    tc = new asterCommand();
		    std::cout<<"create aster module\n";
		}
		else
		{
		    std::cout<<"Unknown module!!! Exit!\n";
		    exit(0);
		}
		std::cout<<"Make Hello str\n";
		std::string message = tc->SayHello();
		message += " {fix bug with get status line}";
		std::cout<<"hello str = "<<message<<"\n";
		for (;;)
		{
			try
			{
				tcp::socket socket(io_main);
				std::cout<<"Prepare accept\n";
				acceptor.accept(socket);
				boost::system::error_code ignored_error;
				std::cout<<"send hello\n";
				
				boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
				
				std::cout<<"run main loop\n";
				while(MainLoop(socket, tc))
				{
					boost::asio::write(socket, boost::asio::buffer("finish"), ignored_error);
					std::cout<<"MOVE CICLE\n";
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
			return ASTER_PBX_DETECTED;
		else if (strcmp(value, "extreg") == 0)
			return FREESWITCH_PBX_DETECTED;
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
		if(module->RunParse(pt))
		{
		   std::cout<<"TRUE ON RUN PARSE check\n"<<ICommand::RESULT_LABEL<<"\n";
			BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child(ICommand::RESULT_LABEL))
			{
				boost::asio::write(socket, boost::asio::buffer(v.second.data()), ignored_error);
				string answer = readStringFromSocket(socket);
				if (answer == "break")
					break;
			}
			
			
		   
		    return 1;
		}
		else
		    std::cout<<"FALSE ON RUN PARSE\n";
	}
	return 0;
}

std::string Server::readStringFromSocket(tcp::socket& socket)
{
	boost::asio::streambuf input;
	boost::system::error_code ignored_error;

	size_t size = boost::asio::read_until(socket, input, "\r\n", ignored_error);
	string str(boost::asio::buffers_begin(input.data()), boost::asio::buffers_begin(input.data()) + input.size());
	input.consume(size);

	return str;
}

int Server::ParseToJson(tcp::socket& socket, boost::property_tree::ptree& pt)
{
	std::stringstream ss;
	boost::asio::streambuf input;
	boost::system::error_code ignored_error;
	try
	{
		ss << readStringFromSocket(socket);
		boost::property_tree::read_json(ss, pt);
		return 1;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
