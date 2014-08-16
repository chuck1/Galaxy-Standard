#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>

gal::itf::shared::shared(): i_(-1) {
}
void    				        gal::itf::shared::__init() {
	registry_.reg(shared_from_this());
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



