#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <exception>
#include <stdio.h>

#include <boost/thread.hpp>

#ifdef GAL_STD_USE_BOOST
#include <boost/serialization/map.hpp>
#endif

#include <gal/itf/shared.hpp>
#include <gal/stl/wrapper.hpp>
#include <gal/stl/verbosity.hpp>

namespace mi = boost::multi_index;

namespace gal { namespace stl {
	template <class T>
	class map:
		public gal::tmp::Verbosity< map<T> >,
		virtual public gal::itf::shared
	{
		public:
			using gal::tmp::Verbosity<map>::printv;
			struct item_not_found: std::exception {
			};
			typedef std::shared_ptr< gal::stl::factory<T> >			factory_shared_type;
			typedef std::shared_ptr<T>					pointer;
			typedef gal::stl::wrapper<T>					wrapper_type;


			typedef std::map<gal::itf::index_type, wrapper_type>		container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::iterator			iterator;

			enum { CONTINUE, BREAK };

			/** @brief Constructor */
			map() {}
			map(factory_shared_type factory): factory_(factory) {}
			/** @brief destructor
			 *
			 * ensure proper shutdown
			 */
			~map()
			{
				assert(container_.empty());
			}
			void					init(gal::itf::shared * const & parent)
			{
				init_shared(parent);
			}
			void					release()
			{
			}
			template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
				boost::lock_guard<boost::mutex> lk(mutex_);

				ar & boost::serialization::make_nvp("container",container_);
			}
			void					insert(pointer const & t) {
				boost::lock_guard<boost::mutex> lk(mutex_);

				auto c = t.use_count(); 

				assert(t);

				// make sure index is initialized
				auto i = gal::itf::shared::static_get_index(t);

				if(i == -1) {
					//shared_ptr<gal::itf::shared> sh(t);
					t->gal::itf::shared::init_shared(_M_shared_parent);
					i = t->get_index();
					printv(INFO, "t->get_index() = %i\n", i);
				}
				
				//gal::stl::wrapper<T> m(t);

				//assert(t.use_count() == (c + 1));

				//std::cout << "t = " << t.get() << std::endl;
				//std::cout << "t->_M_index = " << t->_M_index << std::endl;


				//container_.insert(value_type(i,m));

				auto ret = container_.insert(
						value_type(
							i,
							wrapper_type(t)
							)
						);

				if(!ret.second) {					
					printv(CRITICAL, "not inserted i = %i\n", i);
					abort();
				}

				assert(t.use_count() == (c + 1));

			}
			void			for_each(std::function<void(pointer)> const & f) {
				boost::lock_guard<boost::mutex> lk(mutex_);

				for(auto it = container_.begin(); it != container_.cend(); ++it) {
					auto p = it->second.ptr_;
					assert(p);
					f(p);
				}
			}
			void			for_each_int(::std::function<int(pointer)> const & f) {
				boost::lock_guard<boost::mutex> lk(mutex_);

				int ret;

				for(auto it = container_.begin(); it != container_.cend(); ++it) {
					auto p = it->second.ptr_;
					assert(p);
					ret = f(p);
					if(ret == CONTINUE) {
						continue;
					} else {
						break;
					}
				}
			}
			/** */
			std::shared_ptr<T>			find(std::string name)
			{
				boost::lock_guard<boost::mutex> lk(mutex_);

				for(auto it = container_.begin(); it != container_.cend(); ++it)
				{
					auto p = it->second.ptr_;
					assert(p);
					if(p->_M_name == name) return p;
				}

				return std::shared_ptr<T>();
			}
			std::shared_ptr<T>			find(gal::itf::index_type i) {
				boost::lock_guard<boost::mutex> lk(mutex_);

				auto it = container_.find(i);

				if(it == container_.end()) throw 0;

				return it->second.ptr_;
			}
			/** */
			void					clear()
			{
				printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);
				boost::lock_guard<boost::mutex> lk(mutex_);
				// replaced by deleter objects
				//for(auto it = container_.begin(); it != container_.end(); ++it) {
				//	it->second.ptr_->release();
				//}
				container_.clear();
			}
			/** @brief begin iterator 0
			*/
			pointer					front()
			{
				auto it = begin();
				if(it != end())
					return it->second.ptr_;
				return pointer();
			}
			iterator				begin()
			{
				return container_.begin();
			}
			/** @brief end iterator 0
			*/
			iterator				end() {
				return container_.end();
			}
			/** */
			void					erase(gal::itf::index_type i) {

				while(1) {	
					boost::lock_guard<boost::mutex> lk(mutex_);

					auto it = container_.find(i);

					if(it == container_.cend()) return;//throw item_not_found();

					auto p = it->second.ptr_;

					assert(p);

					// so deadlock can't occur:
					// if object is already locked, release map then try again
					if(!p->mutex_.try_lock()) continue;

					p->release();

					p->mutex_.unlock();

					container_.erase(it);

					return;
				}
			}
			bool				empty() const
			{
				return container_.empty();
			}
		private:
			factory_shared_type		factory_;
			container_type			container_;
			boost::mutex			mutex_;
	};	
}}

#endif





