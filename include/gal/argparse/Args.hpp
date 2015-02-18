#ifndef ARGPARSE_ARGS_HPP
#define ARGPARSE_ARGS_HPP

#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

#include <gal/argparse/decl.hpp>

typedef std::vector< std::string > vec_str;

namespace gal { namespace argparse {
	struct Args
	{
		void		help();
		void		print();
		std::string	get_value_from_long(std::string l);
		bool		has_long(std::string l);

		std::map< std::string, gal::argparse::Arg* >	arg_map_;
	};
}}

#endif
