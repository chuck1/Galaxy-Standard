#ifndef GAL_REGISTRY_HPP
#define GAL_REGISTRY_HPP

#include <map>
#include <memory>

#include <gal/decl.hpp>
#include <gal/stl/verbosity.hpp>
#include <gal/error/no_index.hpp>

#include <gal/object_index.hpp>

namespace gal {
	class registry_base:
		public gal::tmp::Verbosity< gal::registry_base >
	{
	};
	template<typename index_type_,
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
			printv_func(DEBUG);
		}
		void			init()
		{
			_M_next = first();
			_M_ready = true;
		}

		virtual index_type	first() = 0;
		virtual index_type	get_index(S) = 0;
		virtual void		set_index(S, index_type) = 0;
		virtual void		insert(S) = 0;

		index_type_		next()
		{
			printv_func(DEBUG);
			return _M_next++;
		}
		void			reg(S s)
		{
			printv_func(DEBUG);

			if(!_M_ready) {
				abort();
			}

			//gal::managed_object* s0 = s.get();

			//if(s->_M_index == -1) {

			// check to see it the object has an index with this_process
			try {	
				//s->get_index(_M_process_index);
				get_index(s);
			} catch(gal::error::no_index& e) {
				//s->set_index(gal::object_index(
				//	_M_process_index,
				//     	_M_next++));
				set_index(s, next());
			}

			insert(s);

		}
		S		get(index_type i)
		{
			printv_func(DEBUG);
			auto it = _M_map.find(i);
			if(it == _M_map.cend()) {
				throw gal::error::item_not_found();
			}
			return it->second.lock();
		}

		index_type_		_M_next;
		map_type		_M_map;
		bool			_M_ready;
	};

/*	class object_registry:
		public gal::tmp::Verbosity<gal::object_registry>,
		public registry<
				gal::object_index,
				gal::managed_object,
				gal::less_index>	
	{
	public:
		using gal::tmp::Verbosity<gal::object_registry>::printv;

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


