#ifndef GAL_ITF_REGISTRY00_HPP
#define GAL_ITF_REGISTRY00_HPP

#include <memory>
#include <map>
#include <typeindex>

// gal/itf/shared00.hpp
// gal/itf/shared.hpp
// gal/itf/registry.hpp
#include <gal/itf/typedef.hpp>
#include <gal/std/decl.hpp>

#include <gal/stl/verbosity.hpp>

namespace gal {
	class type_registry
	{
	public:
		typedef std::map< gal:::hash_type, std::string > MHS;
		typedef std::map< std::string, gal::itf::hash_type > MSH;
		hash_type		to_hash_code(std::string const & str);
		std::string		to_string(hash_type const & hash);
		template<typename B, typename D>
		void			makeDefaultFunc()
		{
			printv_func(DEBUG);
		
			register_type(std::type_index(typeid(B)));
			register_type(std::type_index(typeid(D)));
	
			auto l = [] () {
				return std::shared_ptr<D>(
						new D(),
						gal::stl::deleter<D>());
			};

			std::function< std::shared_ptr<B>() > f(l);
		
			gal::stl::factory<B>::default_factory_->template add<D>(f);
		}
		/** @brief Register new type index.
		 *
		 * a type must be registered before the conversion
		 * functions will work.
		 */
		void			register_type(std::type_index new_index);
	private:
		MHS			map_hash_string_;
		MSH			map_string_hash_;
	}
}


namespace gal { namespace itf {
	template<typename index_type_,
		typename T_,
		typename index_less_type_ = less<T> >
	class registry00
	{
	public:
		typedef std::map<
			index_type_,
			std::weak_ptr< T_ >,
		       	index_less_type_> map_type;

		registry00(): _M_ready(false)
		{}

		virtual index_type_	first() = 0;

		index_type_		next()
		{
			return _M_next++;
		}
		void			reg(std::shared_ptr<gal::itf::shared00> s)
		{
			printv_func(DEBUG);

			//gal::itf::shared00* s0 = s.get();

			//if(s->_M_index == -1) {

			// check to see it the object has an index with this_process
			try {	
				s->get_index(_M_process_index);
			} catch(gal::itf::no_index& e) {
				s->set_index(gal::index(
							_M_process_index,
						      	_M_next++));
			}




			typedef std::pair<M::iterator, bool> PAIR;

			//auto i = CALL_MEMBER_FN(*s, _M_p_get_index)();

			for(auto i : s->_M_index_table) {

				PAIR p = _M_map.insert(M::value_type(i.second, s));

				if(p.second == false) {
					printv(CRITICAL, "index already taken: %li %li\n",
							i.second._M_p,
							i.second._M_i);
					abort();
				}

			}
		}



		index_type_		_M_next;
		M			_M_map;
		bool			_M_ready;
		};
		class registry10:
			public gal::tmp::Verbosity<gal::itf::registry00>,
			public registry00<gal::index,
			std::weak_ptr< gal::itf::shared00 >,
			gal::less_index>	
		{
			public:
				registry00();
				std::shared_ptr<gal::itf::shared00>	get(gal::index i);
			public:
				void			set_process_index(long int);
				/*
				 * default value is -1
				 */
				long int		_M_process_index;
				long int		_M_next;
			protected:
		};
	}}

#endif


