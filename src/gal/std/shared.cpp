#include <boost/serialization/map.hpp>

#include <gal/registry_object.hpp>
#include <gal/managed_process.hpp>

#include <gal/managed_object.hpp>

typedef gal::managed_object THIS;

void    		        THIS::init(registry_type * r)
//void    		        THIS::init(gal::managed_object * p)
{
	printv_func(DEBUG);

	assert(r);
	
	/*	
	auto r = dynamic_cast<registry_type*>(p);
	
	if(!r) {
		r = p->get_registry();
		if(!r) {
			throw 0;
		}
	}
	*/
	

	
	// find registry
	
	_M_registry_parent = r;
	r->reg(shared_from_this());

	
	//printv(DEBUG, "_M_index = %i\n", _M_index);

	//assert(_M_index != -1);
}
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











