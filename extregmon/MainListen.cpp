#include "MainListen.h"



MainListen::MainListen()
{
}


MainListen::~MainListen()
{
}



// run accept on server and start listen for incoming connection
int MainListen::run(int port)
{
	if((port > 0)&&(port < 65500))
		return 1;
	return 0;
}


// block execution of program and wait for close
int MainListen::stayAndblock()
{
	return 0;
}
