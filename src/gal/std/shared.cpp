#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>

gal::itf::shared::shared(): _M_index(-1) {
}
void    				        gal::itf::shared::__init() {
	std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
	registry_.reg(shared_from_this());
	assert(_M_index != -1);
}
gal::itf::hash_type				gal::itf::shared::hash_code() const {
	::std::type_index type(typeid(*this));
	return type.hash_code();
}
std::string					gal::itf::shared::name() const {
	::std::type_index type(typeid(*this));
	return type.name();
}


gal::itf::registry		gal::itf::shared::registry_;



