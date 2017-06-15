#include "ICommand.h"
#ifdef __linux__
#include <stdio.h>

#endif // __linux__



ICommand::ICommand()
{
}


ICommand::~ICommand()
{
}





// get output from command execution in shell
string ICommand::getConsoleOutput(string command)
{
	char output[1255];
#ifdef __linux__
	FILE* stream = popen(command.c_str(), "r");
	fgets(output, 1024, stream);

	pclose(stream);
#endif // __LINUX__

	


	return output;
}
