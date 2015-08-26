#ifndef GAL_REGISTRY_HPP
#define GAL_REGISTRY_HPP

#include <map>
#include <memory>
#include <mutex>
#include <gal/decl.hpp>
#include <gal/verb/Verbosity.hpp>
#include <gal/error/no_index.hpp>

#include <gal/object_index.hpp>

namespace gal {
	class registry_base:
		public gal::verb::Verbosity< gal::registry_base >
	{
	};
	template<
		typename index_type_,
		typename T_,
		typename index_less_type_ = std::less<T_> >
	class registry:
		public gal::registry_base
	{
	public:
		typedef std::map<
			index_type_,
			std::weak_ptr< T_ >,
		       	index_less_type_> map_type;
		typedef T_ T;
		typedef std::shared_ptr<T_> S;
		typedef index_type_ index_type;

		registry(): _M_ready(false)
		{
		}
		registry&		operator=(registry&& r)
		{
			_M_next=(std::move(r._M_next));
			_M_map=(std::move(r._M_map));
			_M_ready=(std::move(r._M_ready));
			return *this;
		}
		virtual void		init()
		{
			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			_M_next = first();
			_M_ready = true;
		}

		virtual index_type	first() = 0;
		/**
		 * get the this_process index for object s
		 */
		virtual index_type	get_index(S s) = 0;
		/**
		 * set the this_process index for object s
		 */
		virtual void		set_index(S s, index_type) = 0;
		virtual void		v_insert(S) = 0;

		index_type_		next()
		{
			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			printv_func(DEBUG);

			return _M_next++;
		}
		virtual void		reg(S s)
		{
			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);
			printv_func(DEBUG);

			// why??
			if(!_M_ready) {
				abort();
			}
			
			// check to see it the object has an index with this_process
			try {
				// try getting the index
				get_index(s);
			} catch(gal::error::no_index& e) {
				// if not, use the next available index
				set_index(s, next());
			}
			
			// insert each entry of the index table for s into this registry
			v_insert(s);
		}
		S		get(index_type i)
		{
			// lock
			std::lock_guard<std::recursive_mutex> lg(_M_mutex);

			printv_func(DEBUG);

			auto it = _M_map.find(i);
			if(it == _M_map.cend()) {
				throw gal::error::item_not_found();
			}
			return it->second.lock();
		}
	protected:
		index_type_		_M_next;
		map_type		_M_map;
		bool			_M_ready;
	protected:
		/** general mutex for various operations */
		std::recursive_mutex	_M_mutex;
	};

/*	class object_registry:
		public gal::verb::Verbosity<gal::object_registry>,
		public registry<
				gal::object_index,
				gal::managed_object,
				gal::less_index>	
	{
	public:
		using gal::verb::Verbosity<gal::object_registry>::printv;

		object_registry()
			//_M_process_index(0),
			//_M_next(0)
		{
			printv_func(DEBUG);
		}
		std::shared_ptr<gal::managed_object>	get(gal::object_index i);
	public:
		void			set_process_index(long int);
		*
		 * default value is -1
		 *
		long int		_M_process_index;
	};*/
}

#endif


