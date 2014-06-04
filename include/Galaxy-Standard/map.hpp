#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <stdio.h>


#include <boost/multi_index_container.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>


#include <boost/thread.hpp>

#ifdef GAL_STD_USE_BOOST
#include <boost/serialization/map.hpp>
#endif

#include <Galaxy-Standard/wrapper.hpp>

namespace sp = std;
namespace mi = boost::multi_index;

namespace gal {
	namespace std {
	

		template <class T, typename... INDICES> class map {
			public:
			public:
				typedef sp::shared_ptr<gal::std::factory>			factory_shared_type;
				
				typedef sp::shared_ptr<T>					shared_type;
				
				typedef gal::std::wrapper<T>					wrapper_type;

				//typedef ::std::map< gal::std::index_type, gal::std::wrapper< T > >		map_type;
				
				typedef mi::ordered_unique< mi::global_fun< wrapper_type const &, gal::std::index_type const &, wrapper_type::static_get_index > >	index0;
				
				typedef mi::multi_index_container<wrapper_type, mi::indexed_by<index0, INDICES...> >		container_type;

				//typedef mi::nth_index<container_type, 0>::type::iterator	iterator0;

				template<int I> using iterator = typename mi::nth_index<container_type, I>::type::iterator;

				//typedef typename map_type::iterator				iterator;
				//typedef typename map_type::const_iterator			const_iterator;

				//typedef typename map_type::value_type				value_type_const;
				//typedef ::std::pair<gal::std::index_type, gal::std::wrapper< T > >		value_type;

				enum { CONTINUE, BREAK };

				/** @brief Constructor */
				map() {}
				map(factory_shared_type factory): factory_(factory) {}
				/*void		add(value_type& p) {
				  p.first = next_++;
				  map_.insert(p);
				  }*/
				/** */
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					ar & boost::serialization::make_nvp("container",container_);
				}
				void				insert(sp::shared_ptr< T > u) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					assert(u);

					gal::std::wrapper< T > m(u);
					
					//map_.emplace(u->i_, m);
					container_.insert(m);
				}
				template<int I> void		for_each(::std::function<void(iterator<I>)> const & f) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					for(auto it = mi::get<I>(container_).begin(); it != mi::get<I>(container_).cend(); ++it) {
						f(it);
					}
				}
				template<int I> void		for_each_int(::std::function<int(iterator<I>)> const & f) {
					boost::lock_guard<boost::mutex> lk(mutex_);

					int ret;

					for(auto it = mi::get<I>(container_).begin(); it != mi::get<I>(container_).cend(); ++it) {
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

					auto it = container_.find(i);
					return it->second.ptr_;
				}
				/** */
				void					clear() {
					boost::lock_guard<boost::mutex> lk(mutex_);

					for(auto it = mi::get<0>(container_).begin(); it != mi::get<0>(container_).cend(); ++it) {
						it->second.ptr_->release();
					}

					container_.clear();
				}
				/** */
				void				release(gal::std::index_type i) {

					boost::lock_guard<boost::mutex> lk(mutex_);

					auto it = container_.find(i);

					if(it == container_.cend()) return;

					it->second.ptr_->release();

					container_.erase(it);
				}
			private:
				factory_shared_type		factory_;
				container_type			container_;
				boost::mutex			mutex_;
		};	
	}
}

#endif





