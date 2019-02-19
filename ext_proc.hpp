#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include <thread>
#include <future>
#include <utility>
#include <exception>
#include <type_traits>

namespace ExtProc{
	enum RunMode_Await { await  = 1 };
	enum RunMode_Detach{ detach = 2 };
	enum RunOption_WithStdOut{ with_stdout = 3 };
	struct Process{
		using return_type = std::tuple<int, std::string>;
		Process() = delete;
		Process(std::string command);

		void        run(RunMode_Detach);
		return_type run(RunMode_Await, RunOption_WithStdOut);
		int         run(RunMode_Await);

		int join();

	private:
		void run_impl(bool with_stdout = false);
		enum class Phase{
			initialized,
			joinable,
			finished
		};
		static void proc(std::promise<return_type> ret, std::string command, bool get_stdout);
		Phase phase_;
		std::string command_;
		std::future<return_type> return_data_;
	};
}
