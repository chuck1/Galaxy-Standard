#ifndef GAL_STD_ENUM_MAP_HPP
#define GAL_STD_ENUM_MAP_HPP

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

namespace gal {
	template<typename enum_type>
	struct EnumMap
	{
		std::map< std::string, enum_type >		map_string_enum_;
		std::map< enum_type, std::string >		map_enum_string_;
		std::string		toString(enum_type val)
		{
			auto it = map_enum_string_.find(val);
			if(it == map_enum_string_.cend()) throw 0;
			return it->second;
		}
		enum_type		toEnum(::std::string str)
		{
			auto it = map_string_enum_.find(str);
			if(it == map_string_enum_.cend()) throw 0;
			return it->second;
		}
		std::vector< std::string >		toStringVec(enum_type val)
		{
			enum_type e = 0;
			std::vector< ::std::string > vec;
			for(size_t b = 0; b < (sizeof(enum_type) * 8); ++b) {
				e = 1 << b;
				if(e & val) {
					vec.push_back(toString(e));
				}
			}
			return vec;
		}
		enum_type		toEnum(std::vector<std::string> vec)
		{
			enum_type e = 0;
			for(auto it = vec.cbegin(); it != vec.cend(); ++it) {
				e |= toEnum(*it);
			}
			return e;
		}
	};
}

#endif


