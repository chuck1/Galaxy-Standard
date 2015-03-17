#ifndef GAL_ITF_REGISTRY00_HPP
#define GAL_ITF_REGISTRY00_HPP

#include <memory>
#include <map>
#include <typeindex>

// gal/itf/registry.hpp
#include <gal/itf/typedef.hpp>
#include <gal/std/decl.hpp>

#include <gal/stl/verbosity.hpp>

namespace gal { namespace itf {
	class registry00: public gal::tmp::Verbosity<gal::itf::registry00>
	{
	public:
		typedef std::map< gal::itf::hash_type, std::string > MHS;
		typedef std::map< std::string, gal::itf::hash_type > MSH;

		//typedef std::map< index_type, std::weak_ptr< gal::itf::shared > > M;
		typedef std::map< index_type, std::weak_ptr< gal::itf::shared00 > > M;

		registry00();
		std::shared_ptr<gal::itf::shared00>	get(gal::itf::index_type i);
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
	protected:
		M					map_;
		gal::itf::index_type			next_;
	};
}}

#endif

