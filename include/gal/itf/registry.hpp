#ifndef GAL_STD_REGISTRY_HPP
#define GAL_STD_REGISTRY_HPP

/** @file shared.hpp
 */

#include <memory>
#include <map>
#include <typeindex>

#include <gal/std/decl.hpp>
#include <gal/itf/typedef.hpp>

namespace gal { namespace itf {
		class registry
		{
			public:
				registry();
				void								reg(std::shared_ptr< gal::itf::shared > s);
				std::shared_ptr<shared>						get(gal::itf::index_type i);

				std::map< hash_type, std::string >				map_hash_string_;
				std::map< std::string, hash_type >				map_string_hash_;
			private:
				std::map< index_type, std::weak_ptr< gal::itf::shared > >	map_;
				gal::itf::index_type						next_;

		};
}}

#endif

