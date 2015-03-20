#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>

typedef gal::itf::registry THIS;

THIS::registry()
	//_M_p_get_index(&gal::itf::shared::get_index),
	//_M_p_set_index(&gal::itf::shared::set_index)
{
}
/*
THIS::registry(GET_INDEX g, SET_INDEX s):
	_M_p_get_index(g),
	_M_p_set_index(s)
{
}
*/
void			THIS::reg(std::shared_ptr<gal::itf::shared00> s)
{
	printv_func(DEBUG);

	//gal::itf::shared00* s0 = s.get();

	//assert(_M_p_get_index);
	//assert(_M_p_set_index);

	//if(s->_M_index == -1) {
	
	// check to see it the object has an index with this_process

	try {	
		s->get_index(_M_process_index);
	} catch(gal::itf::no_index& e) {
		s->set_index(gal::index(_M_process_index, _M_next++));
	}
	

	/*	
	if(CALL_MEMBER_FN(*s, _M_p_get_index)() == -1) {
		if(_M_p_set_index) {
			printv(DEBUG, "assign index %i\n", next_);
			CALL_MEMBER_FN(*s, _M_p_set_index)(next_++);
		} else {
			printv(CRITICAL, "cannot register\n");
			abort();
		}
	}
	*/
	
	/*
	   auto it = map_.find(s->_M_index);
	   if(it != map_.cend()) {
	   }

	   map_[s->_M_index] = s;
	   */

	typedef std::pair<M::iterator, bool> PAIR;

	//auto i = CALL_MEMBER_FN(*s, _M_p_get_index)();
	
	for(auto i : s->_M_index_table) {
		
	PAIR p = _M_map.insert(M::value_type(i.second, s));

	if(p.second == false) {
		printv(CRITICAL, "index already taken: %li %li\n",
				i.second._M_p,
				i.second._M_i);
		abort();
	}

	}
}






