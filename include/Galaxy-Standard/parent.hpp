#ifndef NEBULA_UTIL_PARENT_HH
#define NEBULA_UTIL_PARENT_HH

#include <Galaxy-Standard/map.hpp>
#include <Galaxy-Standard/shared.hpp>
#include <Galaxy-Standard/wrapper.hpp>



#include <Nebula/Types.hh>

namespace gal {
	namespace std {
		template<class T> class parent: virtual public gal::std::shared {
			public:
				typedef gal::std::map< T >		map_type;
				parent() {
				}
				void					insert(sp::shared_ptr< T > s) {
					map_.insert(s);
				}

				sp::shared_ptr< T >			get(gal::std::index_type i) {
					return map_.find(i);
				}
				void					release(gal::std::index_type i) {
					auto me = sp::dynamic_pointer_cast< gal::std::parent< T > >(shared_from_this());
					
					boost::thread t(boost::bind(
							&gal::std::parent< T >::thread_release,
							me,
							i
							));
					
					t.detach();
				}
			private:
				void					thread_release(gal::std::index_type i) {
					map_.release(i);
				}
			public:
				void					clear() {
					map_.clear();
				}

			
				map_type				map_;
		};
	}
}

#endif




