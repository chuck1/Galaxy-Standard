
#include <gal/verb/VerbosityBase.hpp>

typedef gal::verb::VerbosityBase THIS;

THIS::VerbosityBase()
{}
THIS::~VerbosityBase()
{}
void			THIS::init(std::shared_ptr<VR> r)
{
	//assert(r);
	_M_reg = r;
}
THIS::S_VR		THIS::get_vr() const
{

	auto r = _M_reg.lock();
	if(!r) {
		//auto name = typeid(*this).name();
		//printf("warning: verbosity registry is null. name=%s\n", name);
		//abort();
	}
	return r;
}


