#ifndef HELPER_INFO_HPP
#define HELPER_INFO_HPP

#include <dlfcn.h>

#include <typeindex>
#include <memory>
#include <cassert>
#include <string>

#include <gal/typedef.hpp>
#include <gal/stl/verbosity.hpp>
#include <gal/dll/helper_info.hpp>

#include <boost/serialization/nvp.hpp>

namespace gal { namespace dll {

	//template<typename H> struct deleter;

	struct helper_info:
		public gal::tmp::Verbosity<gal::dll::helper_info>
	{
		public:
			using gal::tmp::Verbosity<gal::dll::helper_info>::printv;
			helper_info();
			/** @brief constructor
			* 
			* @param search_path search path for finding shared library
			*/
			helper_info(std::string search_path);
		public:
			helper_info(std::string f, std::string c, std::type_index ti);

			helper_info(helper_info const & h);

			template<class Archive> void	serialize(Archive & ar, int v)
			{
				ar & BOOST_SERIALIZATION_NVP(file_name);
				ar & BOOST_SERIALIZATION_NVP(class_name);
				ar & BOOST_SERIALIZATION_NVP(base_name);
				ar & BOOST_SERIALIZATION_NVP(base_hc);
			}
		public:
			std::string		file_name;
			std::string		class_name;
			std::string		base_name;
			unsigned long		base_hc;
	};
}}

#endif

