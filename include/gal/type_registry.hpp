#ifndef GAL_TYPE_REGISTRY_HPP
#define GAL_TYPE_REGISTRY_HPP

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
		typedef std::map< gal::hash_type, std::string > MHS;
		typedef std::map< std::string, gal::hash_type > MSH;
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
	};
}


