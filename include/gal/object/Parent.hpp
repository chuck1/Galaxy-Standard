#ifndef GAL_STD_PARENT_HPP
#define GAL_STD_PARENT_HPP

#include <gal/stl/map.hpp> // gal/stl/map.hpp.in
#include <gal/mng/managed_object.hpp>
#include <gal/stl/wrapper.hpp>
#include <gal/object/Child.hpp>
#include <gal/object/ParentBase.hpp>

namespace gal { namespace object {

	template< typename T, typename S_ = std::shared_ptr<T> >
	class Parent:
		virtual public gal::object::ParentBase,
		virtual public gal::mng::managed_object
	{
	public:
		using gal::verb::Verbosity<gal::object::ParentBase>::printv;
		
		friend class boost::serialization::access;
		
		typedef S_				S;
		typedef gal::stl::map<T, S_>		MAP;
		typedef typename MAP::W			W;
		typedef std::shared_ptr<MAP>		MAP_S;
		typedef typename MAP::iterator		ITER;
		typedef typename MAP::FILTER_FUNC	FILTER_FUNC;
		typedef std::lock_guard<std::recursive_mutex>	LOCK;
		
		Parent()
		{
		}
		void			init(gal::mng::managed_object * parent)
		{
			assert_map();
		}
		void			register_all(gal::mng::registry_object * r)
		{
			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			assert_map();
			auto l = [&] (S & s) {
				s->register_all(r);
			};
			_M_map->for_each(l);
		}
		void			change_process_index(
				gal::process_index p0,
				gal::process_index p1)
		{
			printv_func(DEBUG);

			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			assert_map();
			_M_map->change_process_index(p0, p1);
		}
		void			v_insert(S && s)
		{
			printv_func(DEBUG);

			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			assert_map();
			_M_map->insert(std::move(s));
		}
		S			get(gal::object_index i)
		{
			printv_func(DEBUG);

			assert(_M_map);
			return _M_map->find(i);
		}
		/**
		 * all erasure should have to go through this function (how to enfore??)
		 */
		void			erase(gal::object_index i)
		{
			printv_func(DEBUG);

			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			typedef gal::object::Parent< T,S > TYPE;

			auto self = std::dynamic_pointer_cast<TYPE>(shared_from_this());

			boost::thread t(boost::bind(
						&TYPE::thread_erase,
						self,
						i
					));
			
			t.detach();
		}
		void			erase(
				std::shared_ptr<gal::mng::managed_object> s)
		{
			printv_func(DEBUG);

			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			erase(s->get_index());
		}
		void			clear()
		{
			printv_func(DEBUG);

			if(_M_map) //assert(_M_map);
				_M_map->clear();
		}
		S			front(FILTER_FUNC func = FILTER_FUNC())
		{
			assert_map();
			return _M_map->front(func);
		}
		S			random()
		{
			printv_func(DEBUG);

			assert(_M_map);
			return _M_map->random();
		}
		ITER			begin()
		{
			printv_func(DEBUG);

			assert(_M_map);
			return _M_map->begin();
		}
		ITER			end()
		{
			printv_func(DEBUG);

			assert(_M_map);
			return _M_map->end();
		}
		unsigned int		size()
		{
			assert_map();
			return _M_map->size();
		}
		bool			empty()
		{
			if(_M_map) {
				return _M_map->empty();
			}
			return true;
		}
		void			for_each(std::function<void(S &)> const & f)
		{
			printv_func(DEBUG);

			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			assert_map();
			_M_map->for_each(f);
		}
/*		void			for_each(std::function<void(S const &)> const & f)
		{
			assert_map();
			_M_map->for_each(f);
		}
		*/
		void			for_each_int(std::function<int(S &)> const & f)
		{
			printv_func(DEBUG);

			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			assert_map();
			_M_map->for_each_int(f);
		}
		std::unique_lock<std::recursive_mutex>		unique_lock()
		{
			return std::unique_lock<std::recursive_mutex>(_M_mutex);
			//return std::move(std::unique_lock<std::recursive_mutex>(_M_mutex));
		}
	private:
		void			assert_map()
		{
			if(!_M_map) {
				_M_map.reset(new MAP);
				_M_map->init_verb(get_vr());
				_M_map->init(get_registry());
			}
		}

		template<typename ARCHIVE>
		void			load(
				ARCHIVE & ar,
				unsigned int const & version)
		{
			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			printv_func(DEBUG);
			assert_map();
			ar & boost::serialization::make_nvp("map", *_M_map);

			// set the parent of each object
			auto p = dynamic_cast<typename T::parent_t *>(this);

			auto l = [&] (T & t) {
				try {
					t.init(p);
				} catch(gal::object::child_util::except::parent_is_null & e) {
					// if 
					//   initialization fails because an ancestor of
					//   t has a null parent
					// then
					//   not an error
				}
			};
			
			_M_map->for_each(l);
		}
		template<typename ARCHIVE>
		void			save(
				ARCHIVE & ar,
				unsigned int const & version) const
		{
			// lock
			LOCK lg(const_cast< gal::object::Parent<T,S>* >(this)->_M_mutex);

			printv_func(DEBUG);
			//assert_map();
			assert(_M_map);
			ar & boost::serialization::make_nvp("map", *_M_map);
		}
		BOOST_SERIALIZATION_SPLIT_MEMBER();
	protected:
		void			thread_erase(gal::object_index i)
		{
			printv_func(DEBUG);

			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			_M_map->erase(i);
		}
	private:
		/** container */
		MAP_S			_M_map;
		/**
		 * control changes to the container (insert, erase, etc.)
		 */
		std::recursive_mutex	_M_mutex;
	};
}}

#endif




