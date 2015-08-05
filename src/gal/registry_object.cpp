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
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	typedef std::pair<typename map_type::iterator, bool> PAIR;

	// register the object if not already
	s->gal::managed_object::init(this);
	
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
				printv(CRITICAL, "s0 = %16p %s\n", s.get(), typeid(*s).name());
				printv(CRITICAL, "s1 = %16p %s\n", s1.get(), typeid(*s).name());
				printv(CRITICAL, "p = %16li, i = %16li\n",
					i.second._M_p,
					i.second._M_i);
				assert(0);
			}
		} else {
			printv(DEBUG, "index inserted: %8li%8li\n",
					i.second._M_p,
					i.second._M_i);
		}

	}
}
void		THIS::set_index(gal::process_index p)
{
	printv_func(DEBUG);
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	set_process_index(p);

	_M_next._M_p = p;

	gal::managed_process::set_index(p);
}
void		THIS::set_process_index(gal::process_index p_new)
{
	printv_func(INFO);
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	printv(INFO, "_M_map.size(): %u p_old = %li p_new = %li\n",
			_M_map.size(), _M_index._M_i, p_new._M_i);

	gal::process_index p_old = _M_index;
	
	std::vector< std::pair<
		gal::object_index,
		std::weak_ptr<gal::managed_object>> > v;

	printv(INFO, "m.size(): %u\n", _M_map.size());

	auto it = _M_map.begin();
	while(it != _M_map.end()) {
		gal::object_index o = it->first;

		if(o._M_p == p_old) {
			v.emplace_back(
					gal::object_index(p_new, o._M_i),
					it->second);
			it = _M_map.erase(it);
		} else {
			printf("not changing %li %li\n", o._M_p._M_i, o._M_i);
			it++;
		}
	}

	printv(INFO, "v.size(): %u\n", v.size());

	auto it2 = v.begin();
	while(it2 != v.end()) {
		auto s = it2->second.lock();
		if(!s) {
			it2 = v.erase(it2);
		} else {
			s->change_process_index(p_old, p_new);
			it2++;
		}
	}

	printv(INFO, "m.size(): %u\n", _M_map.size());
	
	_M_map.insert(v.begin(), v.end());

	print_table();
}
void		THIS::print_table()
{
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	printf("registry object table\n");
	printf("    %16s%16s%16s\n", "p", "i", "ptr");
	for(auto e : _M_map) {
		auto s = e.second.lock();
		assert(s);
		printf("    %16li%16li%16p\n", e.first._M_p._M_i, e.first._M_i, s.get());
	}
}





