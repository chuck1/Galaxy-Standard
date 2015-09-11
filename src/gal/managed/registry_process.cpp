//#include <gal/mng/managed_object.hpp>
#include <gal/mng/managed_process.hpp>

#include <gal/mng/registry_process.hpp>

typedef gal::mng::registry_process THIS;

THIS::index_type	THIS::first()
{
	printv_func(DEBUG);

	return index_type(0);
}
THIS::index_type	THIS::get_index(S s)
{
	printv_func(DEBUG);

	gal::process_index p = s->gal::mng::managed_process::get_index();

	if(p._M_i == -1)
		throw gal::error::no_index(__FILE__, __LINE__);
	
	return p;
}
void			THIS::set_index(S s, index_type i)
{
	printv_func(DEBUG);

	s->set_index(i);
}
void			THIS::v_insert(S s)
{
	printv_func(DEBUG);

	typedef std::pair<typename map_type::iterator, bool> PAIR;
	
	/*
	if(s->_M_registry_parent != 0) {
		printv(DEBUG, "process has already been inserted\n");
	}

	s->_M_registry_parent = this;
*/

	//for(auto i : s->_M_index_table) {

		PAIR p = _M_map.insert(
				typename map_type::value_type(
					s->_M_index, s));

		if(p.second == false) {
			printv(CRITICAL, "index already taken: %li\n",
					s->_M_index);
			abort();
		}

	//}
}


