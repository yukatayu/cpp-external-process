#include "ext_proc.hpp"

namespace ExtProc{
	Process::Process(std::string command)
			: command_ (command)
			, phase_ (Phase::initialized)
		{ }

	int Process::join(){
		if(phase_ != Phase::joinable)
			throw std::runtime_error("process is not joinable");
		int ret = 0;
		std::tie(ret, std::ignore) = return_data_.get();
		phase_ = Phase::finished;
		return ret;
	}

	void Process::run(RunMode_Detach){
		run_impl(false);
		phase_ = Phase::joinable;
	}

	Process::return_type Process::run(RunMode_Await, RunOption_WithStdOut){
		run_impl(true);
		auto ret = return_data_.get();
		phase_ = Phase::finished;
		return ret;
	}

	int Process::run(RunMode_Await){
		int ret = 0;
		run_impl(false);
		std::tie(ret, std::ignore) = return_data_.get();
		phase_ = Phase::finished;
		return ret;
	}

	void Process::proc(std::promise<return_type> ret, std::string command, bool get_stdout){
		std::string output;
		constexpr int buf_size = 1024;
		char buf[buf_size + 4];
		FILE *ep;
		try{
			if(!(ep = popen(command.data(), "r")))
				throw std::runtime_error("could not open: " + command);
			while(fgets(buf, buf_size, ep))
				if(get_stdout)
					output += buf;
			int return_code = WEXITSTATUS(pclose(ep));
			ret.set_value({return_code, output});
		} catch(...) {
			try {
				ret.set_exception(std::current_exception());
			} catch(...) { }
		}
	}

	void Process::run_impl(bool with_stdout){
		if(phase_ != Phase::initialized)
			throw std::runtime_error("process has been already launched: " + command_);
		std::promise<return_type> p;
		return_data_ = p.get_future();
		std::thread th(&proc, std::move(p), command_, with_stdout);
		th.detach();
	}
}
