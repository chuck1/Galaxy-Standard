#ifndef GAL_ITF_REGISTRY_HPP
#define GAL_ITF_REGISTRY_HPP


#include <memory>
#include <map>
#include <typeindex>

#include <gal/std/decl.hpp>
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
	private:
		MHS					map_hash_string_;
		MSH					map_string_hash_;
		M					map_;
		gal::itf::index_type			next_;
	};
}}

#endif

