
#include <gal/object/ChildBase.hpp>

typedef gal::object::ChildBase THIS;

THIS::S_P		THIS::get_parent_base()
{
	auto s = _M_parent_base.lock();
	assert(s);
	return s;
}

