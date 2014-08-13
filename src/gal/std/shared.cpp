#include <gal/std/registry.hpp>
#include <gal/std/shared.hpp>

gal::std::shared::shared(): i_(-1) {
}
void    				        gal::std::shared::__init() {
	registry_.reg(shared_from_this());
}
gal::std::hash_type				gal::std::shared::hash_code() const {
	::std::type_index type(typeid(*this));
	return type.hash_code();
}
std::string					gal::std::shared::name() const {
	::std::type_index type(typeid(*this));
	return type.name();
}


gal::std::registry		gal::std::shared::registry_;



