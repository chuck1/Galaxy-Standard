#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

#include <gal/argparse/Tag.hpp>

typedef std::vector< std::string > vec_str;

/*
namespace gal { namespace argparse {
	struct Arg: gal::tmp::Verbosity<Arg>
	{
		virtual std::string	name() = 0;
		virtual void		print() = 0;
		vec_str			values_;
	};

	struct Arg_tag: Arg
	{
		Arg_tag(Tag t);
		// -a --apple
		Tag	tag_;
		virtual std::string	name();
		virtual void		print();
	};

	struct Arg_positional: Arg
	{
		// file
		std::string	name_;
	};
}}
*/
#endif
