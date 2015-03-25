#include <gal/stl/verbosity_register.hpp>

typedef gal::tmp::VerbosityRegister THIS;

void		THIS::reg(std::string str, int* i)
{
	_M_map[str] = i;
}
void		THIS::set(std::string str, int i)
{
	auto it = _M_map.find(str);
	if(it == _M_map.end()) {
		printv(ERROR, "no entry: %s\n",
				str.c_str());
		abort();
		return;
	}

	*(it->second) = i;
}


