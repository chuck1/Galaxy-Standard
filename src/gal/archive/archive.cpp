#include <cassert>

#include <gal/archive/archive.hpp>

typedef gal::archive::archive THIS;

THIS::archive():
	_M_shared_parent(0)
{}
gal::itf::shared *	THIS::get_shared_parent()
{
	assert(_M_shared_parent);
	return _M_shared_parent;
}


