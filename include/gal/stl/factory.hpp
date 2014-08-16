#ifndef NEBULA_UTIL_FACTORY_HPP
#define NEBULA_UTIL_FACTORY_HPP

#include <map>
#include <memory>

#include <gal/std/decl.hpp>
#include <gal/std/helper.hpp>
#include <gal/std/funcmap.hpp>
#include <gal/std/typedef.hpp>

namespace sp = std;

namespace gal {
	namespace std {
		/** @brief factory.
		 *
		 * Store and use allocator functions
		 * 
		 * @par Motivation:
		 * create an object who type is unknown but identified by a has_code.
		 * 
		 * @note the app shall hold instances of factory for the various types and use cases
		 */
		template<typename T> class factory: public gal::std::funcmap<T> {
			public:
				typedef sp::shared_ptr<T>	shared;
				typedef gal::std::funcmap<T>	fm;
				/** */
				template<typename... Args> shared					alloc(gal::std::hash_type hash_code, Args&&... args) {
					//auto f = find<Args...>(hash_code);
					//auto f = gal::std::funcmap<T>::find<Args...>(hash_code);
					auto f = fm::template find<Args...>(hash_code);

					return (f->f_)(::std::forward<Args>(args)...);
				}

			public:
				static sp::shared_ptr< factory<T> >					default_factory_;
		};

		template<typename T> sp::shared_ptr< factory<T> >					factory<T>::default_factory_ = 0;
	}
}

#endif





