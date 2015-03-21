#include <boost/serialization/map.hpp>

#include <gal/registry.hpp>
#include <gal/managed_object.hpp>

typedef gal::managed_object THIS;

void    		        THIS::init(registry_type * r)
{
	printv_func(DEBUG);

	assert(parent);

	_M_registry_parent = r;

	// find registry

	r->reg(shared_from_this());

	//printv(DEBUG, "_M_index = %i\n", _M_index);

	//assert(_M_index != -1);
}
void				THIS::release()
{
	printv_func(DEBUG);

}
/*gal::itf::index_type const &	THIS::static_get_index(std::shared_ptr<THIS> ptr)
{
	assert(ptr);
	return ptr->_M_index;
}*/
void			THIS::load(
		boost::archive::polymorphic_iarchive & ar,
		unsigned int const & version)
{
	printv_func(DEBUG);

	ar & BOOST_SERIALIZATION_NVP(_M_index_table);
	ar & BOOST_SERIALIZATION_NVP(_M_name);
}
void			THIS::save(
		boost::archive::polymorphic_oarchive & ar,
		unsigned int const & version) const
{
	printv_func(DEBUG);

	ar & BOOST_SERIALIZATION_NVP(_M_index_table);
	ar & BOOST_SERIALIZATION_NVP(_M_name);
}











