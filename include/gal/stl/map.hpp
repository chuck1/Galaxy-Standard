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

#include <gal/memory/weak_ptr.hpp>
#include <gal/mng/managed_object.hpp>
#include <gal/stl/wrapper.hpp>
#include <gal/verb/Verbosity.hpp>

//namespace mi = boost::multi_index;

namespace gal { namespace stl {
	class map_base:
		virtual public gal::verb::Verbosity<gal::stl::map_base>
	{
	};
	template <typename T_, class S_ = std::shared_ptr<T_> >
	class map:
		virtual public gal::stl::map_base,
		virtual public gal::managed_object
	{
	public:
		using gal::verb::Verbosity<gal::stl::map_base>::printv;

		class item_not_found:
			virtual public std::exception
		{
		public:
			item_not_found(gal::object_index ni):
				i(ni)
			{
				sprintf(buffer,
						"item not found: "
						"%li %li: %s",
						i._M_p._M_i,
						i._M_i,
						__PRETTY_FUNCTION__);
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

		typedef gal::weak_ptr<T>					W;

		typedef gal::stl::wrapper<T, S_>				wrapper_type;
		typedef std::map<gal::object_index, wrapper_type, gal::less_index>	container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::iterator			iterator;
		typedef typename container_type::const_iterator			IC;
		typedef std::function<bool(S&)>					FILTER_FUNC;
		typedef std::lock_guard<std::recursive_mutex>			LOCK;

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
			printv_func(DEBUG);

			gal::managed_object::init(parent);
		}
		void				release()
		{
		}
		template<class Archive>
		void				load(
				Archive & ar, unsigned int const & version)
		{
			printv_func(DEBUG);
			LOCK lk(mutex_);
			assert(container_.empty());
			clear();
			ar & boost::serialization::make_nvp("container", container_);
		}
		template<class Archive>
		void				save(
				Archive & ar, unsigned int const & version) const
		{
			printv_func(DEBUG);
			LOCK lk(const_cast< gal::stl::map<T_,S_>* >(this)->mutex_);
			
			ar & boost::serialization::make_nvp("container", container_);
		}
		BOOST_SERIALIZATION_SPLIT_MEMBER();
		void				insert(S && s)
		{
			printv_func(DEBUG);

			LOCK lk(mutex_);
			
			assert(s);
			
			// make sure index is initialized
			s->gal::managed_object::init(get_registry());
		
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
			LOCK lk(mutex_);

			for(auto it = container_.begin(); it != container_.cend(); ++it) {
				S & p = it->second.ptr_;
				assert(p);
				f(*p);
			}
		}


		void			for_each(std::function<void(S const &)> const & f)
		{
			LOCK lk(mutex_);

			for(auto it = container_.begin(); it != container_.cend(); ++it) {
				S const & p = it->second.ptr_;
				assert(p);
				f(p);
			}
		}
		void			for_each(std::function<void(S &)> const & f)
		{
			LOCK lk(mutex_);

			for(auto it = container_.begin(); it != container_.cend(); ++it) {
				S & p = it->second.ptr_;
				assert(p);
				f(p);
			}
		}
		void			for_each_int(std::function<int(S const &)> const & f) {
			LOCK lk(mutex_);

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
			LOCK lk(mutex_);

			int ret;

			for(auto it = container_.begin(); it != container_.cend(); ++it) {
				S & p = it->second.ptr_;
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
		W			find(std::string name)
		{
			LOCK lk(mutex_);

			for(auto it = container_.begin(); it != container_.cend(); ++it)
			{
				S & p = it->second.ptr_;
				assert(p);
				if(p->_M_name == name) return p;
			}

			return std::shared_ptr<T>();
		}
		W			find(gal::object_index i)
		{
			LOCK lk(mutex_);

			auto it = container_.find(i);

			if(it == container_.end()) throw item_not_found(i);

			return it->second.ptr_;
		}
		/** */
		void			clear()
		{
			printv_func(DEBUG);

			printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);
			LOCK lk(mutex_);
			
			auto l = [](S & s){
				assert(s);
				s->release();
			};
			
			for_each(l);

			// replaced by deleter objects
			//for(auto it = container_.begin(); it != container_.end(); ++it) {
			//	it->second.ptr_->release();
			//}
			container_.clear();
		}
		/** @brief begin iterator 0
		*/
		W			front(FILTER_FUNC func = FILTER_FUNC())
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
		W			random() const
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
			printv_func(DEBUG);

			while(1) {	
				LOCK lk(mutex_);

				auto it = container_.find(i);

				if(it == container_.cend()) return;//throw item_not_found();

				S & p = it->second.ptr_;

				assert(p);

				// so deadlock can't occur:
				// if object is already locked, release map then try again
				if(!p->mutex_.try_lock()) {
					printv(DEBUG, "element mutex is locked, loop and try again");
					continue;
				}

				p->mutex_.unlock();
				
				// this is where release is called.
				p->release();
				
				container_.erase(it);

				return;
			}
		}
		bool				empty() const
		{
			return container_.empty();
		}
		virtual void			change_process_index(
				gal::process_index p_old,
				gal::process_index p_new)
		{
			printv_func(DEBUG);
			printv(DEBUG, "_M_container.size(): %u "
					"p_old = %li p_new = %li\n",
					container_.size(),
					p_old._M_i,
					p_new._M_i);

			// do base class
			gal::managed_object::change_process_index(p_old, p_new);
			
			//typedef std::pair<gal::object_index, wrapper_type> P;
			typedef std::pair<gal::object_index, S> P;
			std::vector<P> v;
		
		lbl1:
			auto it = container_.begin();
			while(it != container_.end()) {
				gal::object_index o = it->first;
		
				if(o._M_p == p_old) {
					gal::object_index o1(p_new, o._M_i);
					
					assert(it->second.ptr_);

					/*
					if(it->second.ptr_) {
						P p(o1, std::move(it->second.ptr_));
						v.push_back(std::move(p));
					}
					*/

					S s(std::move(it->second.ptr_));

					it = container_.erase(it);

					auto ret = container_.insert(
						value_type(
							o1,
							wrapper_type(
								std::move(s))));

					if(!ret.second) {
						printv(CRITICAL, "not inserted i"
								" = %i\n", o);
						abort();
					}
					assert(ret.first->second.ptr_);
					printv(DEBUG, "object moved %i\n", o1);
					goto lbl1;
				} else {
					it++;
				}
			}

			//printv(INFO, "v.size(): %u\n", v.size());

			/*
			   auto it2 = v.begin();
			   while(it2 != v.end()) {
			   if(it2->second.expired()) {
			   it2 = v.erase(it2);
			   } else {
			   it2->second.lock()->change_process_index(p_old, p_new);
			   it2++;
			   }
			   }
			   */

			/*
			auto it2 = v.begin();
			while(it2 != v.end()) {
				assert(it2->second);
				S s(std::move(it2->second));
				assert(s);

				auto ret = container_.insert(
						value_type(
							it2->first,
							wrapper_type(
							std::move(s))));
				assert(ret.second);
			}
			*/
		}

	private:
		factory_shared_type		factory_;
		container_type			container_;
		std::recursive_mutex		mutex_;
	};	
}}

#endif





