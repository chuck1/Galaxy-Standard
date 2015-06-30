
#include <gal/stl/verbosity_base.hpp>

typedef gal::verbosity_base THIS;

void			THIS::init(std::shared_ptr<VR> r)
{
	assert(r);
	_M_reg = r;
}
THIS::S_VR		THIS::get_vr() const
{
	auto name = typeid(*this).name();

	auto r = _M_reg.lock();
	if(!r) {
		printf("warning: verbosity registry is null. name=%s\n", name);
		abort();
	}
	return r;
}


