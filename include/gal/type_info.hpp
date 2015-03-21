#ifndef GAL_TYPE_INFO_HPP
#define GAL_TYPE_INFO_HPP

#include <gal/shared.hpp>
#include <gal/itf/typedef.hpp>

namespace gal {
	template<typename T>
	class type_info:
		virtual public gal::enable_shared_from_this< gal::type_info<T> >
	{
	public:
		using gal::enable_shared_from_this< gal::type_info<T> >::shared_from_this;
		gal::hash_type		hash_code() const
		{
			//std::cout << __PRETTY_FUNCTION__ << std::endl;

			std::type_index type(typeid(*this));

			//std::cout << type.name() << std::endl;
			//std::cout << type.hash_code() << std::endl;

			return type.hash_code();
		}
		std::string			name() const
		{
			//std::cout << __PRETTY_FUNCTION__ << std::endl;

			std::type_index type(typeid(*this));

			//std::cout << type.name() << std::endl;
			//std::cout << type.hash_code() << std::endl;

			return type.name();
		}
	};
}

#endif
