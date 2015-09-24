#include <cstdio>
#include <gal/mng/index_object.hpp>

typedef gal::object_index THIS;

THIS::object_index():
	_M_i(-1)
{
}
THIS::object_index(long int i):
	_M_i(i)
{
}
THIS::object_index(gal::process_index p, long int i):
	_M_p(p),
	_M_i(i)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}
THIS&	THIS::operator++(int)
{
	_M_i++;
	return *this;
}



