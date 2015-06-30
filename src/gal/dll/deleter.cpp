#include <iostream>

#include <gal/_release.hpp>

#include <gal/dll/helper.hpp>

#include <gal/dll/deleter.hpp>

gal::dll::deleter::~deleter()
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}
gal::dll::deleter::deleter(
		std::shared_ptr<helper_base> h,
		FUNC f,
		gal::dll::helper_info hi,
		S_C c):
	_M_helper(h),
	_M_delete(f),
	_M_helper_info(hi),
	_M_class_info(c)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	assert(h);
	assert(f);
	//assert(c);
	//std::cout << "name " << hi_.name << std::endl;
	//std::cout << "hc   " << hi_.hc << std::endl;
}
gal::dll::deleter::deleter(deleter const & d):
	_M_helper(d._M_helper),
	_M_delete(d._M_delete),
	_M_helper_info(d._M_helper_info),
	_M_class_info(d._M_class_info)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	//std::cout << "name " << hi_.name << std::endl;
	//std::cout << "hc   " << hi_.hc << std::endl;
}
gal::dll::deleter::deleter(deleter&& d):
	_M_helper(std::move(d._M_helper)),
	_M_delete(std::move(d._M_delete)),
	_M_helper_info(std::move(d._M_helper_info)),
	_M_class_info(std::move(d._M_class_info))
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	//std::cout << "name " << hi_.name << std::endl;
	//std::cout << "hc   " << hi_.hc << std::endl;
}
void			gal::dll::deleter::operator()(gal::_release * p)
{
	assert(p);

	p->release();

	assert(_M_delete);
	assert(_M_class_info);

	_M_delete(_M_class_info, p);
}
gal::dll::helper_info const	gal::dll::deleter::getHelperInfo()
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	//std::cout << "name " << hi_.name << std::endl;
	//std::cout << "hc   " << hi_.hc << std::endl;
	return _M_helper_info;
}



