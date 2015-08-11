#ifndef GAL_DECL_HPP
#define GAL_DECL_HPP

#include <memory>

#include <gal/typedef.hpp>

enum
{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

namespace gal {
	class generic_factory;

	class managed_object;
	class managed_process;
	class registry_object;
	class registry_process;
	template<typename, typename, typename>
	class registry;
	
	//class _release;

	namespace error {
		class no_index;
	}	
	namespace stl {
		//template<class T, typename... INDICES> class map;
		template<typename T, class S> class map;
		template<typename T, template<typename T2> class S > class funcmap;
		
		template<typename T> class factory;
		//class factory;
		
		template<typename T> class Initializer;
	}
	namespace dll
	{
		class helper_base;
		template<typename T, template<typename T2> class S = std::shared_ptr>
		class helper;
		class class_info_destroy_0;
	}
}

#endif





