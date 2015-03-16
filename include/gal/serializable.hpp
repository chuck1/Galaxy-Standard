#ifndef GAL_SERIALIZABLE_HPP
#define GAL_SERIALIZABLE_HPP

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

// gal/itf/shared.hpp

namespace gal {
	class serializable
	{
	public:
		virtual ~serializable() {}
		virtual void	v_load(boost::archive::polymorphic_iarchive & ar) = 0;
		virtual void	v_save(boost::archive::polymorphic_oarchive & ar) const = 0;
	};
}

#endif


