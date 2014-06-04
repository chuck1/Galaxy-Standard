#include <Galaxy-Standard/registry.hpp>
#include <Galaxy-Standard/shared.hpp>

gal::std::shared::shared(): i_(-1) {
}
void    				        gal::std::shared::init() {
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



