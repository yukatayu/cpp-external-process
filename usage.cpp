#include "ext_proc.hpp"
#include <iostream>

int main(){
	using namespace ExtProc;
	std::string command = R"(/bin/bash -c "echo "start" && sleep 2 && echo finished && exit 4")";

	// -+-+-+-+- //
	//  detach   //
	// -+-+-+-+- //

	Process proc1(command);
	proc1.run(detach);

	// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- //
	//  await (status code + stdout)   //
	// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- //

	Process proc2(command);
	std::tuple<int, std::string> res
		= proc2.run(await, with_stdout);

	// -+-+-+-+-+-+-+-+-+-+- //
	//  await (status code)  //
	// -+-+-+-+-+-+-+-+-+-+- //

	Process proc3(command);
	int ret = proc3.run(await);
	
	// -+-+-+- //
	//  Join   //
	// -+-+-+- //
	proc1.join();
}
