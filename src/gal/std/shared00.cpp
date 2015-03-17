
#include <gal/itf/registry.hpp>

#include <gal/itf/shared00.hpp>

typedef gal::itf::shared00 THIS;

THIS::shared00():
	_M_shared_parent(0),
	_M_index(-1),
	_M_index_creation(-1)
{
	printv_func(DEBUG);
}
THIS::~shared00()
{
	printv_func(DEBUG);
}
gal::itf::index_type		THIS::get_index() const
{
	printv_func(DEBUG);

	return _M_index;
}
gal::itf::index_type		THIS::get_index_creation() const
{
	printv_func(DEBUG);

	return _M_index_creation;
}
void				THIS::set_index(gal::itf::index_type i)
{
	printv_func(DEBUG);

	_M_index = i;
}
void				THIS::set_index_creation(gal::itf::index_type i)
{
	printv_func(DEBUG);

	_M_index_creation = i;
}
void				THIS::register_all(gal::itf::registry * const & r)
{
	r->reg(shared_from_this());
}



