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

#include <gal/itf/shared.hpp>
#include <gal/stl/wrapper.hpp>
#include <gal/stl/verbosity.hpp>

namespace mi = boost::multi_index;

namespace gal { namespace stl {
	template <typename T, class S_ = std::shared_ptr<T> >
	class map:
		public gal::tmp::Verbosity< map<T, S_> >,
		virtual public gal::itf::shared
	{
		public:
			using gal::tmp::Verbosity<map>::printv;
			struct item_not_found: std::exception {
			};
			typedef std::shared_ptr< gal::stl::factory<T> >			factory_shared_type;

			//typedef std::shared_ptr<T>					S;
			typedef S_							S;

			typedef gal::stl::wrapper<T, S_>				wrapper_type;
			typedef std::map<gal::itf::index_type, wrapper_type>		container_type;
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
			void				init(gal::itf::shared * const & parent)
			{
				init_shared(parent);
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
				//auto i = gal::itf::shared::static_get_index(s);
				auto i = s->get_index();
				
				if(i == -1) {
					//shared_ptr<gal::itf::shared> sh(t);
					s->gal::itf::shared::init_shared(_M_shared_parent);
					i = s->get_index();
					printv(DEBUG, "t->get_index() = %i\n", i);
				}

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
			void			for_each(std::function<void(S const &)> const & f)
			{
				boost::lock_guard<boost::mutex> lk(mutex_);

				for(auto it = container_.begin(); it != container_.cend(); ++it) {
					auto p = it->second.ptr_;
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
			S			find(gal::itf::index_type i)
			{
				boost::lock_guard<boost::mutex> lk(mutex_);

				auto it = container_.find(i);

				if(it == container_.end()) throw 0;

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
			void			erase(gal::itf::index_type i)
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





