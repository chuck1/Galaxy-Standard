#ifndef GAL_STD_PARENT_HH
#define GAL_STD_PARENT_HH

#include <Galaxy-Standard/map.hpp>
#include <Galaxy-Standard/shared.hpp>
#include <Galaxy-Standard/wrapper.hpp>


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
				void					erase(gal::std::index_type i) {

					auto me = sp::dynamic_pointer_cast< gal::std::parent< T > >(shared_from_this());
					
					boost::thread t(boost::bind(
							&gal::std::parent< T >::thread_erase,
							me,
							i
							));
					
					t.detach();
				}
			private:
				void					thread_erase(gal::std::index_type i) {
					map_.erase(i);
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



