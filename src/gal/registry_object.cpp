#include <gal/managed_object.hpp>

#include <gal/registry_object.hpp>

typedef gal::registry_object THIS;

THIS::registry_object()
{
	printv_func(INFO);
}
THIS::index_type	THIS::first()
{
	printv_func(INFO);

	return index_type();
}
THIS::index_type	THIS::get_index(S s)
{
	printv_func(INFO);

	return s->get_index(_M_index);
}
void			THIS::set_index(S s, index_type i)
{
	printv_func(INFO);

	s->set_index(i);
}
void			THIS::insert(S s)
{
	printv_func(INFO);

	typedef std::pair<typename map_type::iterator, bool> PAIR;
	
	if(s->_M_registry_parent != 0) {
		printv(DEBUG, "object has already been inserted\n");
	}

	s->_M_registry_parent = this;

	for(auto i : s->_M_index_table) {

		PAIR p = _M_map.insert(
				typename map_type::value_type(
					i.second, s));

		if(p.second == false) {
			printv(CRITICAL, "index already taken: %li %li\n",
					i.second._M_p,
					i.second._M_i);
			abort();
		}

	}
}


