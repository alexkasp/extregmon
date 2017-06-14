#include "MainListen.h"
#include "Server.h"

int main()
{
	Server srv;
	    srv.startListen(7524);
	return 0;
}