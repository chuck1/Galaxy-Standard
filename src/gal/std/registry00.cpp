#include <vector>

#include <gal/managed_object.hpp>
#include <gal/managed_object.hpp>

#include <gal/registry.hpp>

typedef gal::itf::registry00 THIS;

void		THIS::set_process_index(long int p_new)
{
	printv_func(DEBUG);

	long int p_old = _M_process_index;
	
	std::vector< std::pair<gal::index, std::weak_ptr<gal::managed_object>> > v;

	auto it = _M_map.begin();
	while(it != _M_map.end()) {
		if(it->first._M_p == p_old) {
			v.emplace_back(gal::index(p_new, it->first._M_i),
					it->second);
			it = _M_map.erase(it);
		} else {
			it++;
		}
	}

	auto it2 = v.begin();
	while(it2 != v.end()) {
		if(it2->second.expired()) {
			it2 = v.erase(it2);
		} else {
			it2->second.lock()->change_process_index(p_old, p_new);
			it2++;
		}
	}
	
	_M_map.insert(v.begin(), v.end());
}







