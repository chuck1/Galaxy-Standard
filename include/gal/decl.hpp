#ifndef GAL_DECL_HPP
#define GAL_DECL_HPP

#include <memory>

#include <gal/itf/typedef.hpp>

namespace gal {
	class managed_object;
	class managed_process;
	class registry_object;
	class registry_process;
	template<typename, typename, typename>
	class registry;
	
	class release;

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
	}
}

#endif





