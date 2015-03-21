#ifndef GAL_REGISTRY_HPP
#define GAL_REGISTRY_HPP

#include <gal/object_index.hpp>

namespace gal {
	template<typename index_type_,
		typename T_,
		typename index_less_type_ = std::less<T_> >
	class registry
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
		{}

		virtual index_type	first() = 0;
		virtual index_type	get_index(S) = 0;
		virtual void		set_index(S, index_type) = 0;

		index_type_		next()
		{
			return _M_next++;
		}
		void			reg(S s)
		{
			printv_func(DEBUG);

			//gal::itf::shared00* s0 = s.get();

			//if(s->_M_index == -1) {

			// check to see it the object has an index with this_process
			try {	
				//s->get_index(_M_process_index);
				get_index(s);
			} catch(gal::itf::no_index& e) {
				//s->set_index(gal::object_index(
				//	_M_process_index,
				//     	_M_next++));
				set_index(s, next());
			}

			typedef std::pair<typename map_type::iterator, bool> PAIR;

			for(auto i : s->_M_index_table) {

				PAIR p = _M_map.insert(map_type::value_type(
							i.second, s));

				if(p.second == false) {
					printv(CRITICAL, "index already taken: %li %li\n",
							i.second._M_p,
							i.second._M_i);
					abort();
				}

			}
		}
		S		get(index_type i)
		{
			printv_func(DEBUG);
			auto it = _M_map.find(i);
			if(it == _M_map.cend()) {
				throw 0;
			}
			return it->second.lock();
		}

		index_type_		_M_next;
		map_type		_M_map;
		bool			_M_ready;
	};

	class object_registry:
		public gal::tmp::Verbosity<gal::object_registry>,
		public registry<
				gal::object_index,
				gal::managed_object,
				gal::less_index>	
	{
	public:
		THIS::registry00():
			_M_process_index(0),
			_M_next(0)
		{
			printv_func(DEBUG);
		}
		std::shared_ptr<gal::itf::shared00>	get(gal::object_index i);
	public:
		void			set_process_index(long int);
		/*
		 * default value is -1
		 */
		long int		_M_process_index;
	};
}

#endif


