#include "ext_proc.hpp"
#include <iostream>

int main(){
	using namespace ExtProc;
	std::string command = R"(/bin/bash -c "echo "start" && sleep 2 && echo finished && exit 4")";

	// -+-+-+-+- //
	//  detach   //
	// -+-+-+-+- //

	Process proc1(command);
	proc.run(await, with_stdout);

	// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- //
	//  await (status code + stdout)   //
	// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- //

	Process proc2(command);
	std::tuple<int, std::string> res
		= proc.run(await, with_stdout);

	// -+-+-+-+-+-+-+-+-+-+- //
	//  await (status code)  //
	// -+-+-+-+-+-+-+-+-+-+- //

	Process proc3(command);
	int ret = proc.run(await, with_stdout);
	
}
