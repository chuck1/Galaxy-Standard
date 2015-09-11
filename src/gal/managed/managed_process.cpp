#include <gal/error/no_index.hpp>
#include <gal/mng/managed_process.hpp>

typedef gal::mng::managed_process THIS;

gal::process_index	THIS::get_index() const
{
	if(_M_index == -1) {
		//throw gal::error::no_index();
	}
	return _M_index;
}
void			THIS::set_index(gal::process_index i)
{
	_M_index = i;
}

