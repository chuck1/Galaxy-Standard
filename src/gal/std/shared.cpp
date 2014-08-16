#include <gal/std/registry.hpp>
#include <gal/std/shared.hpp>

gal::itf::shared::shared(): i_(-1) {
}
void    				        gal::itf::shared::__init() {
	registry_.reg(shared_from_this());
}
gal::std::hash_type				gal::itf::shared::hash_code() const {
	::std::type_index type(typeid(*this));
	return type.hash_code();
}
std::string					gal::itf::shared::name() const {
	::std::type_index type(typeid(*this));
	return type.name();
}


gal::itf::registry		gal::itf::shared::registry_;



