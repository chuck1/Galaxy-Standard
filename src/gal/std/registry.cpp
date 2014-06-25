#include <Galaxy-Standard/registry.hpp>
#include <Galaxy-Standard/shared.hpp>


gal::std::registry::registry(): next_(0) {
}
void                                            gal::std::registry::reg(sp::shared_ptr<gal::std::shared> s) {
	if(s->i_ == -1) s->i_ = next_++;

	map_[s->i_] = s;
}
sp::shared_ptr<gal::std::shared>		gal::std::registry::get(gal::std::index_type i) {
	auto it = map_.find(i);

	if(it == map_.cend()) return sp::shared_ptr<gal::std::shared>();

	return it->second.lock();
}





