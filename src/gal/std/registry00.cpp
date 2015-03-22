#include <vector>

#include <gal/managed_object.hpp>
#include <gal/managed_object.hpp>

#include <gal/registry_object.hpp>

typedef gal::registry_object THIS;

void		THIS::set_process_index(long int p_new)
{
	printv_func(DEBUG);

	auto p_old = _M_index;
	
	std::vector< std::pair<gal::object_index, std::weak_ptr<gal::managed_object>> > v;

	auto it = _M_map.begin();
	while(it != _M_map.end()) {
		if(it->first._M_p == p_old) {
			v.emplace_back(gal::object_index(p_new, it->first._M_i),
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







