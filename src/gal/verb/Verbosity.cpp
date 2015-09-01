#include <gal/verb/Verbosity.hpp>

pid_t gettid()
{
	//pid_t tid = syscall(SYS_gettid);
	pid_t tid = syscall(186);
	return tid;
}

