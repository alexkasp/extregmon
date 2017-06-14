#pragma once
class MainListen
{
public:
	MainListen();
	virtual ~MainListen();
	// run accept on server and start listen for incoming connection
	int run(int port);
	// block execution of program and wait for close
	int stayAndblock();
};

