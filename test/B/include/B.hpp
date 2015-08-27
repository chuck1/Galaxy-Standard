#ifndef B_HPP
#define B_HPP

#include <gal/managed_object.hpp>

#include <A.hpp>

namespace gal { namespace test {
struct B: virtual gal::test::A
{
	virtual ~B() {}
	virtual void foo();

	template<typename AR>
	void serialize(AR & ar, unsigned int const &)
	{
		printf("%s\n", __PRETTY_FUNCTION__);
		ar & boost::serialization::base_object<A>(*this);
	}

	virtual void	v_load(ba::polymorphic_iarchive & ar)
	{
		ar & *this;
	}
	virtual void	v_save(ba::polymorphic_oarchive & ar)
	{
		ar & *this;
	}

};
}}
BOOST_CLASS_EXPORT_KEY(gal::test::B)

#endif

