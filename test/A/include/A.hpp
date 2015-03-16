#ifndef A_HPP
#define A_HPP

#include <boost/serialization/export.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

namespace ba = boost::archive;

#include <gal/itf/shared.hpp>

struct A: virtual gal::itf::shared
{
	virtual ~A() {}
	virtual void foo() = 0;
	virtual void release();
	template<typename AR>
	void serialize(AR & ar, unsigned int const &)
	{
		printf("%s\n", __PRETTY_FUNCTION__);
		ar & boost::serialization::base_object<gal::itf::shared>(*this);
	}

	virtual void	v_load(ba::polymorphic_iarchive & ar) = 0;
	virtual void	v_save(ba::polymorphic_oarchive & ar) = 0;
};

BOOST_CLASS_EXPORT_KEY(A);

#endif
