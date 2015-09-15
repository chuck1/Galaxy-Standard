#include <gal/error/base.hpp>

#include <gal/verb/VerbosityBase.hpp>
#include <gal/verb/VerbosityRegistry.hpp>

typedef gal::verb::VerbosityBase THIS;

THIS::VerbosityBase()
{
}
THIS::VerbosityBase(VerbosityBase && v):
	_M_info_default(std::move(v._M_info_default))
{
}
THIS::~VerbosityBase()
{
}
THIS::S_R		THIS::get_vr() const
{
	auto r = _M_reg.lock();
	if(r) {

	} else {
		auto name = typeid(*this).name();
		printf("warning: verbosity registry is null. name=%s\n",
				name);

		gal::error::backtrace bt; bt.calc();
		throw gal::error::base(bt);
	}
	return r;
}
THIS::S_I		THIS::get_info_default() const
{
	//gal::error::backtrace bt; bt.calc();
	//throw gal::error::base(bt);

	assert(_M_info_default);
	return _M_info_default;
}



