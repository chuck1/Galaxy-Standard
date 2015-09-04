#ifndef NEBULA_ENUM_HPP
#define NEBULA_ENUM_HPP

#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <boost/serialization/vector.hpp>

#include <map>

#include <gal/EnumMap.hpp>

#define DEFINE_TYPE(name, values)\
struct name {\
public:\
	typedef long int T;\
	enum E: T\
	{\
		BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_VALUE, , values)\
	};\
	name(): val_((E)0) {}\
	name(E e): val_(e) {}\
	name(unsigned int e): val_((E)e) {}\
	\
	operator T()\
	{\
		return (T)val_;\
	}\
	std::string		toString() const\
	{\
		return maps_.maps_.toString(val_);\
	}\
	\
	void		save(\
		boost::archive::xml_oarchive & ar, unsigned int const & version)\
	{\
		std::vector< ::std::string > vec = maps_.maps_.toStringVec(val_);\
		ar << boost::serialization::make_nvp("value",vec);\
	}\
	void				load(boost::archive::xml_iarchive & ar, unsigned int const & version) {\
	std::vector< ::std::string > vec;\
		ar >> boost::serialization::make_nvp("value",vec);\
		val_ = (E)maps_.maps_.toEnum(vec);\
	}\
	template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {\
		ar & boost::serialization::make_nvp("value",val_);\
	}\
	E		val_;\
private:\
	struct Maps {\
		Maps() {\
			BOOST_PP_SEQ_FOR_EACH(DEFINE_MAP_STRING_ENUM_VALUE, , values)\
			BOOST_PP_SEQ_FOR_EACH(DEFINE_MAP_ENUM_STRING_VALUE, , values)\
		}\
		gal::EnumMap<T>		maps_;\
	};\
	static Maps	maps_;\
};\


#define DEFINE_TYPE_STATICS(name)\
	name::Maps name::maps_;

#define DEFINE_ENUM_VALUE(r, data, elem)\
	BOOST_PP_SEQ_HEAD(elem) = BOOST_PP_SEQ_TAIL(elem) BOOST_PP_COMMA()

#define DEFINE_MAP_STRING_ENUM_VALUE(r, data, elem)\
	maps_.map_string_enum_[BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem))] = (E)BOOST_PP_SEQ_TAIL(elem);

#define DEFINE_MAP_ENUM_STRING_VALUE(r, data, elem)\
	maps_.map_enum_string_[(E)BOOST_PP_SEQ_TAIL(elem)] = BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem));

#endif


