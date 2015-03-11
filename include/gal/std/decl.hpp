#ifndef GAL_DECL_HPP
#define GAL_DECL_HPP

namespace gal {
	namespace itf {
		class registry;
		class shared;
	}
	namespace stl {
		//template<class T, typename... INDICES> class map;
		template<typename T, class S> class map;
		template<typename T> class funcmap;
		
		template<typename T> class factory;
		//class factory;
		
		template<typename T> class Initializer;
	}
	namespace dll
	{
		template<typename T> class helper;
	}
}

#endif





