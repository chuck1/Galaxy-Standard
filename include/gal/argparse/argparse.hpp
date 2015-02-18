#ifndef ARGPARSE_ARGPARSE_HPP
#define ARGPARSE_ARGPARSE_HPP

#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

#include <gal/argparse/decl.hpp>

typedef std::vector< std::string > vec_str;

namespace gal { namespace argparse {
	struct ValuesEmpty
	{
	};

	Arg*		make_arg(vec_str words);
	vec_str		split(char * str);
	vec_str		split(int ac, char ** av);
}}

#endif
