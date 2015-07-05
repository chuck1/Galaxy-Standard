/*#include <gal/argparse/Arg.hpp>
#include <gal/argparse/Parser.hpp>
*/
/*
gal::argparse::Args		gal::argparse::Parser::parse(
		int ac, char ** av, char const * format)
{
	Args ret;

	auto words = split(ac, av);

	vec_str temp;
	for(unsigned int i = 0; i < words.size(); i++)
	{
		if(words[i][0] == '-')
		{
			//printv(DEBUG, "tag '%s'\n", words[i].c_str());
			
			if(temp.empty()) temp.push_back(words[i]);
			else {
				Arg* a = make_arg(temp);
				if(a != 0) {
					ret.arg_map_[a->name()] = a;
				}
				temp.clear();
				temp.push_back(words[i]);
			}
		}
		else
		{
			//printv(DEBUG, "value %s\n", words[i].c_str());
			temp.push_back(words[i]);
		}
	}

	if(!temp.empty())
	{
		if(temp[0][0] == '-') {
			Arg* a = make_arg(temp);
			ret.arg_map_[a->name()] = a;
		} else {
		}
	}

	ret.help();
	ret.print();

	return ret;
};
*/

