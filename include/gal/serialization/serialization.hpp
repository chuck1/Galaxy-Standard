#ifndef GAL_SERIALIZATION_SERIALIZATION_HPP
#define GAL_SERIALIZATION_SERIALIZATION_HPP

#include <boost/tuple/tuple.hpp>

#include <gal/stl/helper.hpp>

namespace gal {
	template<typename A, typename T, int S>
	int			serialize_0(
			A & ar,
			T & t,
			unsigned int const & v)
	{
		ar & std::get<S>(t);
		return 0;
	}
	template<typename A, typename T, int... S>
	void			serialize_1(
			A & ar,
			T & t,
			unsigned int const & v,
			gal::seq<S...> s)
	{
		gal::pass(serialize_0<A, T, S>(ar, t, v)...);
	}
}

namespace boost { namespace serialization {
	template<typename A, typename... T>
	void			serialize(
			A & ar,
			std::tuple<T...> & t,
			unsigned int const & v)
	{
		typedef typename gal::gens<sizeof...(T)>::type seq_type;
	
		gal::serialize_1(ar, t, v, seq_type());
	}
}}

#endif

