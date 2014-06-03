#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <stdio.h>

#include <boost/thread.hpp>

#ifdef GAL_STD_USE_BOOST
#include <boost/serialization/map.hpp>
#endif

#include <Galaxy-Standard/wrapper.hpp>

namespace sp = std;

namespace gal {
	namespace std {
		template <class T> class map {
			public:
				typedef ::std::weak_ptr< gal::std::factory >			factory_weak;

				typedef ::std::map< gal::std::index_type, gal::std::wrapper< T > >		map_type;

				typedef typename map_type::iterator				iterator;
				typedef typename map_type::const_iterator			const_iterator;

				typedef typename map_type::value_type				value_type_const;
				typedef ::std::pair<gal::std::index_type, gal::std::wrapper< T > >		value_type;

				enum { CONTINUE, BREAK };

				/** @brief Constructor */
				map() {}
				map(factory_weak factory): factory_(factory) {}
				/*void		add(value_type& p) {
				  p.first = next_++;
				  map_.insert(p);
				  }*/
				/** */
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					ar & boost::serialization::make_nvp("map",map_);
				}
				void				insert(sp::shared_ptr< T > u) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					assert(u);

					gal::std::wrapper< T > m(u);
					
					//map_.emplace(u->i_, m);
					map_[u->i] = m;
				}
				void				for_each(::std::function<void(const_iterator)> const & f) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					for(auto it = map_.cbegin(); it != map_.cend(); ++it) {
						f(it);
					}
				}
				void				for_each_int(::std::function<int(const_iterator)> const & f) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					int ret;

					for(auto it = map_.cbegin(); it != map_.cend(); ++it) {
						ret = f(it);
						if(ret == CONTINUE) {
							continue;
						} else {
							break;
						}
					}
				}
				/** */
				sp::shared_ptr<T>			find(gal::std::index_type i) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					auto it = map_.find(i);
					return it->second.ptr_;
				}
				/** */
				void				clear() {
					boost::lock_guard<boost::mutex> lk(mutex_);

					for(auto it = map_.cbegin(); it != map_.cend(); ++it) {
						it->second.ptr_->release();
					}

					map_.clear();
				}
				/** */
				void				release(gal::std::index_type i) {

					boost::lock_guard<boost::mutex> lk(mutex_);

					auto it = map_.find(i);

					if(it == map_.cend()) return;

					it->second.ptr_->release();

					map_.erase(it);
				}
			private:
				factory_weak			factory_;
				map_type			map_;
				boost::mutex			mutex_;
		};	
	}
}

#endif





