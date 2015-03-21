#ifndef NEBULA_UTIL_FACTORY_HPP
#define NEBULA_UTIL_FACTORY_HPP

#include <map>
#include <memory>

#include <gal/std/decl.hpp>
#include <gal/stl/helper.hpp>
#include <gal/stl/funcmap.hpp>
#include <gal/itf/typedef.hpp>

namespace sp = std;

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
		class factory: public gal::stl::funcmap<T>
		{
		public:
			typedef std::shared_ptr<T>	shared;
			typedef gal::stl::funcmap<T>	fm;
			/** */
			template<typename... Args>
			shared				alloc(gal::hash_type hash_code, Args&&... args)
			{
				//auto f = find<Args...>(hash_code);
				//auto f = gal::stl::funcmap<T>::find<Args...>(hash_code);
				
				// get allocator function from funcmap using hashcode
				auto f = fm::template find<Args...>(hash_code);

				return (f->f_)(::std::forward<Args>(args)...);
			}
		public:
			static std::shared_ptr< factory<T> >				default_factory_;
		};

		template<typename T> std::shared_ptr< factory<T> > factory<T>::default_factory_ = std::shared_ptr< factory<T> >(new factory<T>());
}}

#endif


