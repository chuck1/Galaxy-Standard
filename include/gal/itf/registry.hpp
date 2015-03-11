#ifndef GAL_ITF_REGISTRY_HPP
#define GAL_ITF_REGISTRY_HPP


#include <memory>
#include <map>
#include <typeindex>


#include <gal/std/decl.hpp>
#include <gal/stl/deleter.hpp>
#include <gal/itf/typedef.hpp>

namespace gal { namespace itf {
	class registry
	{
	public:
		typedef std::map< gal::itf::hash_type, std::string > MHS;
		typedef std::map< std::string, gal::itf::hash_type > MSH;
		typedef std::map< index_type, std::weak_ptr< gal::itf::shared > > M;
		registry();
		void					reg(std::shared_ptr<gal::itf::shared> s);
		std::shared_ptr<gal::itf::shared>	get(gal::itf::index_type i);
		hash_type				to_hash_code(std::string const & str);
		std::string				to_string(hash_type const & hash);
		/** @brief Register new type index.
		 *
		 * a type must be registered before the conversion functions will work.
		 */
		void					register_type(std::type_index new_index);

		template<typename B, typename D>
		void					makeDefaultFunc()
		{
			//LOG(lg, neb::fnd::sl, debug) << __PRETTY_FUNCTION__;
		
			register_type(std::type_index(typeid(B)));
			register_type(std::type_index(typeid(D)));
		
			std::function< std::shared_ptr<B>() > f(
					[]() { return std::shared_ptr<D>(new D(), gal::stl::deleter<D>()); }
					);
		
			gal::stl::factory<B>::default_factory_->template add<D>(f);
		}

	private:
		MHS					map_hash_string_;
		MSH					map_string_hash_;
		M					map_;
		gal::itf::index_type			next_;
	};
}}

#endif

