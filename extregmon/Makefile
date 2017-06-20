	BUILDHEADERS = -I ./include -I /usr/include/mysql++ -I /usr/include/mysql -I /usr/local/include/hiredis
default:
	export CFLAGS="$CFLAGS -O0 -fbuiltin -g"
	export CXXFLAGS="$CXXFLAGS -O0 -fbuiltin -g"
	
	g++ -g main.cpp -o main ICommand.cpp MainListen.cpp Server.cpp testCommand.cpp asterCommand.cpp -std=c++11 -L /usr/local/boost/lib/ -L /usr/lib64/ -L /usr/lib64/mysql/ \
	-Wl,-Bstatic -lhiredis -lboost_system -lboost_random -lboost_regex  -lboost_thread -lboost_date_time -lboost_log -lboost_log_setup -lboost_filesystem -Wl,-Bdynamic -lpthread -lm -lcurl -lrt
