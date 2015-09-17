#ifndef NEBULA_UTIL_FACTORY_HPP
#define NEBULA_UTIL_FACTORY_HPP

#include <map>
#include <memory>

#include <gal/decl.hpp>
#include <gal/typedef.hpp>
#include <gal/stl/helper.hpp>
#include <gal/stl/funcmap.hpp>
#include <gal/stl/object_map.hpp> // gal/stl/object_map.hpp.in

namespace gal { namespace stl {
		/** @brief factory.
		 *
		 * Store and use allocator functions
		 * 
		 * @par Motivation:
		 * create an object whose type is unknown but identified by a hash_code.
		 * 
		 * @note the app shall hold instances of factory for the various types and use cases
		 * like local and remote??? how does this work?
		 */
		template<typename T>
		class factory:
			virtual public gal::stl::funcmap<T, std::shared_ptr>,
			virtual public gal::stl::object__<T>
		{
		public:
			typedef std::shared_ptr<T>	shared;
			typedef gal::stl::funcmap<T, std::shared_ptr>	fm;
			/** */
			template<typename... Args>
			shared				alloc(size_t h, Args&&... args)
			{
				//auto f = find<Args...>(hash_code);
				//auto f = gal::stl::funcmap<T>::find<Args...>(hash_code);
				
				// get allocator function from funcmap using hashcode
				auto f = fm::template find<Args...>(h);

				//return (f->f_)(std::forward<Args>(args)...);
				return (*f)(std::forward<Args>(args)...);
			}
		public:
			//static std::shared_ptr< factory<T> >		default_factory_;
		};

		//template<typename T>
		//std::shared_ptr< factory<T> > factory<T>::default_factory_ = std::shared_ptr< factory<T> >(new factory<T>());
}}

#endif


