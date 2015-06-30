#include <gal/managed_object.hpp>

#include <gal/registry_object.hpp>

typedef gal::registry_object THIS;

THIS::registry_object()
{
}
THIS::index_type	THIS::first()
{
	printv_func(DEBUG);

	return index_type(gal::managed_process::get_index(), 0);
}
THIS::index_type	THIS::get_index(S s)
{
	printv_func(DEBUG);

	return s->get_index(_M_index);
}
void			THIS::set_index(S s, index_type i)
{
	printv_func(DEBUG);
	
	s->set_index(i);
}
void			THIS::insert(S s)
{
	printv_func(DEBUG);

	typedef std::pair<typename map_type::iterator, bool> PAIR;
	
	if(s->_M_registry_parent != 0) {
		printv(DEBUG, "registry_parent already set\n");
	}
	
	s->_M_registry_parent = this;

	for(auto i : s->_M_index_table) {

		PAIR p = _M_map.insert(
				typename map_type::value_type(
					i.second, s));

		if(p.second == false) {
			printv(DEBUG, "key already taken: %li %li\n",
					i.second._M_p,
					i.second._M_i);
			
			S s1 = _M_map[i.second].lock();
			
			printv(DEBUG, "s = %p, s1 = %p\n", s.get(), s1.get());

			if(s.get() == s1.get()) {
				printv(DEBUG, "index already inserted\n");
			} else {
				printv(CRITICAL, "duplicate index error\n");
				abort();
			}
		} else {
			printv(DEBUG, "index inserted: %li %li\n",
					i.second._M_p,
					i.second._M_i);
		}

	}
}
void		THIS::set_index(gal::process_index p)
{
	printv_func(DEBUG);

	set_process_index(p);

	_M_next._M_p = p;

	gal::managed_process::set_index(p);
}
void		THIS::set_process_index(gal::process_index p_new)
{
	printv_func(DEBUG);
	printv(DEBUG, "_M_map.size(): %u p_old = %li p_new = %li\n",
			_M_map.size(), _M_index._M_i, p_new._M_i);

	gal::process_index p_old = _M_index;
	
	std::vector< std::pair<
		gal::object_index,
		std::weak_ptr<gal::managed_object>> > v;

	auto it = _M_map.begin();
	while(it != _M_map.end()) {
		gal::object_index o = it->first;

		if(o._M_p == p_old) {
			v.emplace_back(
					gal::object_index(p_new, o._M_i),
					it->second);
			it = _M_map.erase(it);
		} else {
			it++;
		}
	}

	printv(DEBUG, "v.size(): %u\n", v.size());

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






