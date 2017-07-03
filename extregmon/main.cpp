#include "MainListen.h"
#include "Server.h"
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	Server srv;
	    srv.startListen(7524);
	return 0;
}