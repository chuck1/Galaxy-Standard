#ifndef ARGPARSE_PARSER_HPP
#define ARGPARSE_PARSER_HPP

#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

#include <gal/argparse/Args.hpp>
#include <gal/argparse/argparse.hpp>

typedef std::vector< std::string > vec_str;

namespace gal { namespace argparse {
	class Parser
	{
		public:
			Args	parse(int ac, char ** av, char const * format);
	};
}}

#endif
