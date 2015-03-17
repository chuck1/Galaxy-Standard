#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>

typedef gal::itf::registry THIS;

THIS::registry():
	_M_p_get_index(0),
	_M_p_set_index(0)
{
}
THIS::registry(GET_INDEX g, SET_INDEX s):
	_M_p_get_index(g),
	_M_p_set_index(s)
{
}
void			THIS::reg(std::shared_ptr<gal::itf::shared00> s)
{
	printv_func(DEBUG);

	//gal::itf::shared00* s0 = s.get();

	assert(_M_p_get_index);
	//assert(_M_p_set_index);

	//if(s->_M_index == -1) {
	if(CALL_MEMBER_FN(*s, _M_p_get_index)() == -1) {
		if(_M_p_set_index) {
			printv(DEBUG, "assign index %i\n", next_);
			CALL_MEMBER_FN(*s, _M_p_set_index)(next_++);
		} else {
			printv(CRITICAL, "cannot register\n");
			abort();
		}
	}

	/*
	   auto it = map_.find(s->_M_index);
	   if(it != map_.cend()) {
	   }

	   map_[s->_M_index] = s;
	   */

	typedef std::pair<M::iterator, bool> PAIR;

	auto i = CALL_MEMBER_FN(*s, _M_p_get_index)();

	PAIR p = map_.insert(M::value_type(i, s));

	if(p.second == false) {
		printv(CRITICAL, "index already taken\n");
		abort();
	}
}





