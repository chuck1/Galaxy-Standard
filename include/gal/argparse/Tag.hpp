#ifndef ARGPARSE_TAG_HPP
#define ARGPARSE_TAG_HPP

#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

typedef std::vector< std::string > vec_str;

namespace gal { namespace argparse {
	struct Tag
	{
		Tag(std::string w)
		{
			if(w[1] == '-')
			{
				assert(w.size() > 2);
				long_ = w.substr(2);
			}
			else
			{
				assert(w.size() > 1);
				short_ = w.substr(1);
			}
		}

		std::string	short_;
		std::string	long_;
	};
}}

#endif
