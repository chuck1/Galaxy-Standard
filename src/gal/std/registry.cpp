#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>


gal::itf::registry::registry(): next_(0) {
}
void                                            gal::itf::registry::reg(std::shared_ptr<gal::itf::shared> s) {
	if(s->i_ == -1) s->i_ = next_++;

	map_[s->i_] = s;
}
std::shared_ptr<gal::itf::shared>		gal::itf::registry::get(gal::itf::index_type i) {
	auto it = map_.find(i);

	if(it == map_.cend()) return std::shared_ptr<gal::itf::shared>();

	return it->second.lock();
}





