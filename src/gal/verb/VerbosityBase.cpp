
#include <gal/verb/VerbosityBase.hpp>
#include <gal/verb/VerbosityRegistry.hpp>

typedef gal::verb::VerbosityBase THIS;

THIS::VerbosityBase()
{}
THIS::~VerbosityBase()
{}
THIS::S_R		THIS::get_vr() const
{

	auto r = _M_reg.lock();
	if(r) {


	} else {
		//auto name = typeid(*this).name();
		//printf("warning: verbosity registry is null. name=%s\n", name);
		//abort();
	}
	return r;
}


