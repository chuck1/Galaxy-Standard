#include <boost/serialization/map.hpp>

#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>

typedef gal::itf::shared THIS;

void    		        THIS::init_shared(THIS * const & parent)
{
	printv_func(DEBUG);

	//printv_func(DEBUG);

	assert(parent);

	_M_shared_parent = parent;

	// find registry

	auto reg = get_registry();	

	reg->reg(shared_from_this());

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











