#ifndef GAL_STD_REGISTRY_HPP
#define GAL_STD_REGISTRY_HPP

/** @file shared.hpp
 */

#include <memory>
#include <map>
#include <typeindex>

#include <Galaxy-Standard/decl.hpp>
#include <Galaxy-Standard/typedef.hpp>

namespace sp = std;

namespace gal {
	namespace std {
		class registry {
			public:
				registry();
				void								reg(sp::shared_ptr< gal::std::shared > s);
				sp::shared_ptr<shared>						get(gal::std::index_type i);
			private:
				::std::map< index_type, sp::weak_ptr< gal::std::shared > >	map_;
				gal::std::index_type						next_;

		};
	}
}

#endif
