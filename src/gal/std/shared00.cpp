
#include <gal/itf/registry.hpp>

#include <gal/itf/shared.hpp>
#include <gal/itf/shared00.hpp>

typedef gal::itf::shared00 THIS;

THIS::shared00():
	_M_shared_parent(0)
	//_M_index(-1),
	//_M_index_creation(-1)
{
	printv_func(DEBUG);
}
THIS::~shared00()
{
	printv_func(DEBUG);
}
gal::index		THIS::get_index() const
{
	printv_func(DEBUG);
	
	auto r = get_registry();

	return get_index(r->_M_process_index);
}
gal::index		THIS::get_index(long int p) const
{
	printv_func(DEBUG);
	auto it = _M_index_table.find(p);
	if(it == _M_index_table.cend()) {
		printv(ERROR, "process index not found: %li\n", p);
		throw gal::itf::no_index();
	}
	return it->second;
}
/*
gal::index		THIS::get_index_creation() const
{
	printv_func(DEBUG);

	return _M_index_creation;
}
*/
void				THIS::set_index(gal::index i)
{
	printv_func(DEBUG);

	std::pair<std::map<long int, gal::index>::iterator, bool> p = _M_index_table.insert(std::make_pair(i._M_p, i));

	if(!p.second) {
		abort();
	}
}
/*void				THIS::set_index_creation(gal::index i)
{
	printv_func(DEBUG);
	_M_index_creation = i;
}*/
void				THIS::register_all(gal::itf::registry * const & r)
{
	r->reg(shared_from_this());
}
gal::itf::registry *		THIS::get_registry()
{
	printv_func(DEBUG);

	auto r = dynamic_cast<gal::itf::registry *>(this);

	if(r) return r;

	auto p = _M_shared_parent;

	assert(p);

	return p->get_registry();
}
gal::itf::registry const *	THIS::get_registry() const
{
	printv_func(DEBUG);

	auto r = dynamic_cast<gal::itf::registry const *>(this);

	if(r) return r;

	auto p = _M_shared_parent;

	assert(p);

	return p->get_registry();
}
void				THIS::change_process_index(
		long int p_old,
		long int p_new)
{
	printv_func(DEBUG);


	std::vector< std::pair<long, gal::index> > v;

	auto it = _M_index_table.begin();
	while(it != _M_index_table.end()) {
		if(it->first == p_old) {
			printv(INFO, "change process index from %li to %li. object index: %li\n",
				p_old, p_new, it->second._M_i);

			v.emplace_back(p_new,
					gal::index(p_new, it->second._M_i));
			it = _M_index_table.erase(it);
		} else {
			it++;
		}
	}

	_M_index_table.insert(v.begin(), v.end());

}


