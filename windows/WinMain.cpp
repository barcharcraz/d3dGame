//this library contains the entry point
//to the program, it calls the main function
#include "stdafx.h"
#include <Utils/strings.h>
#include "ComUtils.h"
//the main function, if this is not
//defined someplace you have bigger problems
extern int main(int, char**);


//the unicode winmain entrypoint, note that we have to 
//do some major fucking around with strings here to narrow the array
//of widestrings
int CALLBACK wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR cmdLine, int nCmdShow) {
	hinstance;
	hPrevInstance;
	cmdLine;
	nCmdShow;
	windows::ComInitialize com;
	int argc = __argc;
	std::vector<std::string> narrowParams;
	char ** argv = new char*[argc];
	for (int i = 0; i < argc; ++i) {
		narrowParams.push_back(utils::narrow(std::wstring{ cmdLine[i] }));
		argv[i] = new char[narrowParams[i].size() + 1];
		std::copy(narrowParams[i].begin(), narrowParams[i].end(), argv[i]);
		argv[i][narrowParams[i].size()] = '\0';

	}
	auto retval = main(argc, argv);
	//this is to satisfy memory checkers and what have you
	//the process is going away anyways
	for (int i = 0; i < argc; ++i) {
		delete[] argv[i];
	}
	delete[] argv;
	return retval;
}