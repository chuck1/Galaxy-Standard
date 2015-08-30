#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cxxabi.h>

#define SIZE 100

#include <gal/error/backtrace.hpp>

typedef gal::error::backtrace THIS;

THIS::backtrace(THIS const & bt):
	_M_strings(bt._M_strings)
{
}
THIS::backtrace()
{
}
void		THIS::calc()
{
	void *buffer[SIZE];

	int nptrs = ::backtrace(buffer, SIZE);
	//printf("backtrace() returned %d addresses\n", nptrs);

	/* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
	 *        would produce similar output to the following: */
	
	char ** strings;

	strings = backtrace_symbols(buffer, nptrs);
	if(strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	//const int len = 512;
	//char sbuffer[len];
	
	for(int j = 0; j < nptrs; j++) {
		
		int status;
		
		char * ret = abi::__cxa_demangle(strings[j], 0, 0, &status);
		
		if(ret != 0) {
			_M_strings.push_back(std::string(ret));
		} else {
			_M_strings.push_back(std::string(strings[j]));
		}
	}
}
void		THIS::print() const
{
	for (unsigned int j = 0; j < _M_strings.size(); j++)
		printf("%s\n", _M_strings[j].c_str());
}



