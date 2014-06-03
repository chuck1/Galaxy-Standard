#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__

/** @file shared.hpp
 */

#include <memory>
#include <map>
#include <typeindex>
#include <string>

#include <Galaxy-Standard/decl.hpp>
#include <Galaxy-Standard/typedef.hpp>


namespace sp = std;

namespace gal {
	namespace std {
		/** @brief %shared.
		 *
		 * Avoid multiple enabled_shared_from_this bases.
		 * Provide common base for working with factory and map.
		 * Supply type info.
		 *
		 */
		class shared:
			virtual public sp::enable_shared_from_this<shared>
		{
			public:
				
				
			public:
				shared();
				/** @brief Destructor */
				virtual ~shared() {}
				virtual void					init();
			public:
				/** @brief Hash Code */
				hash_type					hash_code() const;
				/** */
				::std::string					name() const;
				/** */
				static hash_type				to_hash_code(::std::string const & str) {
					auto it = map_string_hash_.find(str);
					if(it == map_string_hash_.cend()) throw 0;
					return it->second;
				}
				/** */
				static ::std::string const &			to_string(hash_type const & hash) {
					auto it = map_hash_string_.find(hash);
					if(it == map_hash_string_.cend()) throw 0;
					return it->second;
				}
				/** @brief Register new type index.
				 * a type must be registered before the conversion functions will work.
				 */
				static void					register_type(::std::type_index new_index) {
					map_hash_string_[new_index.hash_code()] = new_index.name();
					map_string_hash_[new_index.name()] = new_index.hash_code();
				}
			public:
				index_type						i_;
			public:
				static gal::std::registry				registry_;
				static ::std::map<hash_type, ::std::string>		map_hash_string_;
				static ::std::map< ::std::string, hash_type >		map_string_hash_;

		};
	}
}

#endif

