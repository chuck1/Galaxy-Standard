#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <exception>
#include <stdio.h>
#include <stdlib.h>

#include <boost/thread.hpp>

#ifdef GAL_STD_USE_BOOST
#include <boost/serialization/map.hpp>
#endif

#include <gal/managed_object.hpp>
#include <gal/stl/wrapper.hpp>
#include <gal/stl/verbosity.hpp>

namespace mi = boost::multi_index;

namespace gal { namespace stl {
	template <typename T_, class S_ = std::shared_ptr<T_> >
	class map:
		public gal::tmp::Verbosity< map<T_, S_> >,
		virtual public gal::managed_object
	{
		public:
			using gal::tmp::Verbosity<map>::printv;
			struct item_not_found: std::exception {
				item_not_found(gal::object_index ni):
					i(ni)
				{
					sprintf(buffer, "item not found: %li %li: %s", i._M_p._M_i, i._M_i, __PRETTY_FUNCTION__);
				}
				virtual const char * what() const noexcept
				{
					char * ret = new char[128];
					strcpy(ret, buffer);
					return ret;
				}
				char buffer[128];
				gal::object_index i;
			};
			typedef std::shared_ptr< gal::stl::factory<T_> >		factory_shared_type;

			//typedef std::shared_ptr<T>					S;
			typedef T_							T;
			typedef S_							S;

			typedef gal::stl::wrapper<T, S_>				wrapper_type;
			typedef std::map<gal::object_index, wrapper_type, gal::less_index>	container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::iterator			iterator;
			typedef typename container_type::const_iterator			IC;
			typedef std::function<bool(S&)>					FILTER_FUNC;
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
			//void				init(gal::managed_object * parent)
			void				init(gal::registry_object * parent)
			{
				gal::managed_object::init(parent);
			}
			void				release()
			{
			}
			template<class Archive>
			void				serialize(Archive & ar, unsigned int const & version) {
				boost::lock_guard<boost::mutex> lk(mutex_);

				ar & boost::serialization::make_nvp("container", container_);
			}
			void				insert(S && s)
			{
				boost::lock_guard<boost::mutex> lk(mutex_);
				
				//std::weak_ptr<T> w(s);
				
				assert(s);
				
				// make sure index is initialized
				s->gal::managed_object::init(_M_registry_parent);
			
				// get this_process index
				gal::object_index i = s->gal::managed_object::get_index();
				
				/*
				if(i == -1) {
					//shared_ptr<gal::managed_object> sh(t);
					
					i = s->get_index();
					printv(DEBUG, "t->get_index() = %i\n", i);
				}
				*/

				auto ret = container_.insert(
						value_type(
							i,
							wrapper_type(std::move(s))));

				if(!ret.second) {					
					printv(CRITICAL, "not inserted i = %i\n", i);
					abort();
				}
				
				//return w;
			}
			void			for_each(std::function<void(T &)> const & f)
			{
				boost::lock_guard<boost::mutex> lk(mutex_);

				for(auto it = container_.begin(); it != container_.cend(); ++it) {
					auto p = it->second.ptr_;
					assert(p);
					f(*p);
				}
			}


			void			for_each(std::function<void(S const &)> const & f)
			{
				boost::lock_guard<boost::mutex> lk(mutex_);

				for(auto it = container_.begin(); it != container_.cend(); ++it) {
					S const & p = it->second.ptr_;
					assert(p);
					f(p);
				}
			}
			void			for_each(std::function<void(S &)> const & f)
			{
				boost::lock_guard<boost::mutex> lk(mutex_);

				for(auto it = container_.begin(); it != container_.cend(); ++it) {
					S & p = it->second.ptr_;
					assert(p);
					f(p);
				}
			}
			void			for_each_int(std::function<int(S const &)> const & f) {
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
			void			for_each_int(std::function<int(S &)> const & f) {
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
			S			find(std::string name)
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
			S			find(gal::object_index i)
			{
				boost::lock_guard<boost::mutex> lk(mutex_);

				auto it = container_.find(i);

				if(it == container_.end()) throw item_not_found(i);

				return it->second.ptr_;
			}
			/** */
			void			clear()
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
			S			front(FILTER_FUNC func = FILTER_FUNC())
			{
				if(func) {
					for(auto it = container_.begin(); it != container_.cend(); ++it) {
						S& s = it->second.ptr_;
						assert(s);
						if(func(s))
							return s;
					}
				} else {
					auto it = begin();
					if(it != end())
						return it->second.ptr_;
				}
				return S();
			}
			S			random() const
			{
				if(empty()) return S();
				
				unsigned int i = rand() % size();

				auto it = cbegin();
				
				std::advance(it, i);

				assert(it != cend());

				return it->second.ptr_;
			}
			IC			cbegin() const
			{
				return container_.cbegin();
			}
			IC			cend() const
			{
				return container_.cend();
			}
			iterator		begin()
			{
				return container_.begin();
			}
			iterator		end()
			{
				return container_.end();
			}
			unsigned int		size() const
			{
				return container_.size();
			}
			void			erase(gal::object_index i)
			{

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





