
#include <gal/registry.hpp>

#include <gal/managed_process.hpp>
#include <gal/registry_object.hpp>
#include <gal/error/no_index.hpp>

#include <gal/managed_object.hpp>

typedef gal::managed_object THIS;

THIS::managed_object():
	_M_registry_parent(0)
	//_M_index(-1),
	//_M_index_creation(-1)
{
	printv_func(DEBUG);
}
THIS::~managed_object()
{
	printv_func(DEBUG);
}
gal::object_index		THIS::get_index() const
{
	printv_func(DEBUG);
	
	auto r = get_registry();

	return get_index(r->_M_index);
}
gal::object_index		THIS::get_index(gal::process_index p) const
{
	printv_func(DEBUG);
	
	long i = p._M_i;

	if(i == -1) {
		//printv(ERROR, "invalid process index\n");
		//throw 0;
	}

	auto it = _M_index_table.find(p);
	if(it == _M_index_table.cend()) {
		printv(DEBUG, "process index not found: %li\n", i);
		throw gal::error::no_index();
	}
	return it->second;
}
/*
gal::object_index		THIS::get_index_creation() const
{
	printv_func(DEBUG);

	return _M_index_creation;
}
*/
void				THIS::set_index(gal::object_index i)
{
	printv_func(DEBUG);

	std::pair<map_type::iterator, bool> p = _M_index_table.insert(std::make_pair(i._M_p, i));

	if(!p.second) {
		abort();
	}
}
/*void				THIS::set_index_creation(gal::object_index i)
{
	printv_func(DEBUG);
	_M_index_creation = i;
}*/
void				THIS::register_all(registry_type * r)
{
	r->reg(shared_from_this());
}
THIS::registry_type *		THIS::get_registry()
{
	printv_func(DEBUG);
	
	if(_M_registry_parent) return _M_registry_parent;
	
	// this could be a registry
	auto r = dynamic_cast<registry_type*>(this);
	if(r) {
		_M_registry_parent = r;
		return r;
	}
	
	printv(CRITICAL, "registry_parent is null and this is not a registry\n");

	abort();
	
	return 0;
}
THIS::registry_type const *	THIS::get_registry() const
{
	printv_func(DEBUG);
	
	if(_M_registry_parent) return _M_registry_parent;
	
	// this could be a registry
	auto r = dynamic_cast<registry_type const * const>(this);
	if(r) {
		//_M_registry_parent = r;
		return r;
	}
	
	abort();

	printv(CRITICAL, "registry_parent is null and this is not a registry\n");
	
	return 0;
}
void				THIS::change_process_index(
		gal::process_index p_old,
		gal::process_index p_new)
{
	printv_func(DEBUG);

	std::vector< std::pair<gal::process_index, gal::object_index> > v;

	auto it = _M_index_table.begin();
	while(it != _M_index_table.end()) {
		if(it->first == p_old) {
			printv(DEBUG, "change process index from %li to %li. object index: %li\n",
				p_old, p_new, it->second._M_i);

			v.emplace_back(p_new,
					gal::object_index(p_new, it->second._M_i));
			it = _M_index_table.erase(it);
		} else {
			it++;
		}
	}

	_M_index_table.insert(v.begin(), v.end());

}


