#include <gal/stl/verbosity_register.hpp>

typedef gal::tmp::VerbosityRegistry THIS;

/*
void		THIS::reg(std::string str, int* i)
{
	auto p = _M_map.insert(value_type(str, i));

	if(!p.second) {
		printv(CRITICAL, "not inserted: %s %p\n",
				str.c_str(), i);
		abort();
	}

	printv(INFO, "inserted: %s %p\n",
			str.c_str(), i);
}
void		THIS::set(std::string str, int i)
{
	auto it = _M_map.find(str);
	if(it == _M_map.end()) {
		printv(ERROR, "no entry: %s\n",
				str.c_str());
		return;
	}

	*(it->second) = i;
}
*/

