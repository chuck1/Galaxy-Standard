#include <gal/managed_object.hpp>

#include <gal/registry_object.hpp>

typedef gal::registry_object THIS;

THIS::registry_object()
{
	printv_func(DEBUG);
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
		printv(INFO, "registry_parent already set\n");
	}
	
	s->_M_registry_parent = this;

	for(auto i : s->_M_index_table) {

		PAIR p = _M_map.insert(
				typename map_type::value_type(
					i.second, s));

		if(p.second == false) {
			printv(CRITICAL, "key already taken: %li %li\n",
					i.second._M_p,
					i.second._M_i);
			
			S s1 = _M_map[i.second].lock();
			
			printv(CRITICAL, "s = %p, s1 = %p\n", s.get(), s1.get());

			if(s.get() == s1.get()) {
				printv(CRITICAL, "index already inserted\n");
			} else {
				printv(CRITICAL, "duplicate index error\n");
				abort();
			}
		} else {
			printv(INFO, "index inserted: %li %li\n",
					i.second._M_p,
					i.second._M_i);
		}

	}
}


