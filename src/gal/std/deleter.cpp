#include <iostream>


#include <gal/itf/shared.hpp>

#include <gal/dll/deleter.hpp>

#include <gal/dll/helper.hpp>


gal::dll::deleter::~deleter()
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}
gal::dll::deleter::deleter(
		std::shared_ptr<helper_base> h,
		std::function<void(gal::itf::shared*)> f,
		gal::dll::helper_info hi):
	_M_helper(h),
	_M_delete(f),
	_M_helper_info(hi)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	assert(h);
	assert(f);
	//std::cout << "name " << hi_.name << std::endl;
	//std::cout << "hc   " << hi_.hc << std::endl;
}
gal::dll::deleter::deleter(deleter const & d):
	_M_helper(d._M_helper),
	_M_delete(d._M_delete),
	_M_helper_info(d._M_helper_info)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	//std::cout << "name " << hi_.name << std::endl;
	//std::cout << "hc   " << hi_.hc << std::endl;
}
gal::dll::deleter::deleter(deleter&& d):
	_M_helper(std::move(d._M_helper)),
	_M_delete(std::move(d._M_delete)),
	_M_helper_info(std::move(d._M_helper_info))
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	//std::cout << "name " << hi_.name << std::endl;
	//std::cout << "hc   " << hi_.hc << std::endl;
}
void			gal::dll::deleter::operator()(gal::itf::shared* p)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	assert(p);

	p->release();

	assert(_M_delete);

	_M_delete(p);
}
gal::dll::helper_info const	gal::dll::deleter::getHelperInfo()
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	//std::cout << "name " << hi_.name << std::endl;
	//std::cout << "hc   " << hi_.hc << std::endl;
	return _M_helper_info;
}



