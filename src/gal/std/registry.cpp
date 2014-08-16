#include <gal/std/registry.hpp>
#include <gal/std/shared.hpp>


gal::itf::registry::registry(): next_(0) {
}
void                                            gal::itf::registry::reg(sp::shared_ptr<gal::itf::shared> s) {
	if(s->i_ == -1) s->i_ = next_++;

	map_[s->i_] = s;
}
sp::shared_ptr<gal::itf::shared>		gal::itf::registry::get(gal::std::index_type i) {
	auto it = map_.find(i);

	if(it == map_.cend()) return sp::shared_ptr<gal::itf::shared>();

	return it->second.lock();
}





