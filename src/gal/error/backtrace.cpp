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
std::string demangle(const char* symbol)
{
	size_t size;
	int status;
	char temp[128];
	char* demangled;
	//first, try to demangle a c++ name
	if (1 == sscanf(symbol, "%*[^(]%*[^_]%127[^)+]", temp)) {
		if (NULL != (demangled = abi::__cxa_demangle(temp, NULL, &size, &status))) {
			std::string result(demangled);
			free(demangled);
			return result;
		}
	}
	//if that didn't work, try to get a regular c symbol
	if (1 == sscanf(symbol, "%127s", temp)) {
		return temp;
	}

	//if all else fails, just return the symbol
	return symbol;
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
		_M_strings.push_back(demangle(strings[j]));
	}
	
}
void		THIS::print() const
{
	printf("BACKTRACE\n");
	for (unsigned int j = 0; j < _M_strings.size(); j++)
		printf("    %s\n", _M_strings[j].c_str());
}



