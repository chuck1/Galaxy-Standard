#include <gal/mng/managed_object.hpp>

#include <gal/mng/registry_object.hpp>

typedef gal::mng::registry_object THIS;

THIS::registry_object()
{
}
void			THIS::init()
{
	BASE_REGISTRY::init();
}
void			THIS::reg(S s)
{
	BASE_REGISTRY::reg(s);
}
THIS::S			THIS::get(index_type i)
{
	return BASE_REGISTRY::get(i);
}
THIS::index_type	THIS::first()
{
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	printv_func(DEBUG);

	return index_type(gal::mng::managed_process::get_index(), 0);
}
THIS::index_type	THIS::get_index(S s)
{
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	printv_func(DEBUG);

	return s->get_index(_M_index);
}
void			THIS::set_index(S s, index_type i)
{
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	printv_func(DEBUG);
	
	s->set_index(i);
}
void			THIS::v_insert(S s)
{
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	printv_func(DEBUG);


	typedef std::pair<typename map_type::iterator, bool> PAIR;

	// register the object if not already
	s->gal::mng::managed_object::init(this);
	
	for(auto i : s->_M_map_index._M_map) {

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

	gal::mng::managed_process::set_index(p);
}
void		THIS::set_process_index(gal::process_index p_new)
{
	printv_func(DEBUG);
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	printv(DEBUG, "_M_map.size(): %u p_old = %li p_new = %li\n",
			_M_map.size(), _M_index._M_i, p_new._M_i);

	gal::process_index p_old = _M_index;
	
	std::vector< std::pair<
		gal::object_index,
		std::weak_ptr<gal::mng::managed_object>> > v;

	printv(DEBUG, "m.size(): %u v.size(): %u\n", _M_map.size(), v.size());

	auto it = _M_map.begin();
	while(it != _M_map.end()) {
		gal::object_index o = it->first;

		if(o._M_p == p_old) {
			v.emplace_back(
					gal::object_index(p_new, o._M_i),
					it->second);
			it = _M_map.erase(it);
			printv(DEBUG, "erase    m.size(): %u v.size(): %u\n", _M_map.size(), v.size());
		} else {
			printv(DEBUG, "not changing %li %li\n", o._M_p._M_i, o._M_i);
			it++;
		}
	}

	printv(DEBUG, "m.size(): %u v.size(): %u\n", _M_map.size(), v.size());

	int c0= 0;
	int c1= 0;

	auto it2 = v.begin();
	while(it2 != v.end()) {
		auto i = it2->first;
		auto s = it2->second.lock();
		printv(DEBUG, "processing %8li %8li\n", i._M_p._M_i, i._M_i);
		if(!s) {
			printv(DEBUG, "erase from v %li %li\n", i._M_p._M_i, i._M_i);
			it2 = v.erase(it2);
			++c0;
		} else {
			printv(DEBUG, "change process index: %24p %s\n", typeid(*s).name());
			s->change_process_index(p_old, p_new);
			it2++;
			++c0;
		}
	}

	printv(DEBUG, "looped %i %i %i times\n", c0, c1, c0+c1);

	printv(DEBUG, "m.size(): %u v.size(): %u\n", _M_map.size(), v.size());

	//print_table();
	
	_M_map.insert(v.begin(), v.end());

	printv(DEBUG, "m.size(): %u v.size(): %u\n", _M_map.size(), v.size());

	//print_table();
}
void		THIS::print_table()
{
	// lock
	std::lock_guard<std::recursive_mutex> lg(_M_mutex);

	printf("registry object table\n");
	printf("    %16s%16s%16s\n", "p", "i", "ptr");

	for(auto e : _M_map) {
		auto s = e.second.lock();
	
		if(s) {
			printf("    %16li%16li%24p%s\n",
					e.first._M_p._M_i,
					e.first._M_i,
					s.get(),
					typeid(*s).name());
		}
	}
}





