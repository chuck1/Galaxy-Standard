#include <boost/serialization/map.hpp>

#include <gal/mng/registry.hpp>

#include <gal/mng/managed_process.hpp>
#include <gal/mng/registry_object.hpp>
#include <gal/error/no_index.hpp>

#include <gal/mng/managed_object.hpp>

typedef gal::managed_object THIS;

THIS::managed_object():
	_M_registry_parent(0)
	//_M_index(-1),
	//_M_index_creation(-1)
{
	//printv_func(DEBUG);
}
THIS::~managed_object()
{
	//printv_func(DEBUG);
}
void    		        THIS::init(registry_type * r)
//void    		        THIS::init(gal::managed_object * p)
{
	assert(r);

	gal::verb::VerbosityBase::init(r->get_vr());

	printv_func(DEBUG);

	//if(_M_flag.any(flag::INITIALIZED)) return;
	
	// use _M_registry_parent to determine if this needs to be registered
	if(_M_registry_parent == 0) {
		printv(DEBUG, "managed_object registering\n");
		_M_registry_parent = r;
		r->reg(shared_from_this());
	}
	//_M_flag.set(flag::INITIALIZED);
	
	//printv(DEBUG, "_M_index = %i\n", _M_index);

	//assert(_M_index != -1);
}
gal::object_index		THIS::get_index()
{
	printv_func(DEBUG);
	
	auto r = get_registry();
	
	gal::object_index i;


	try {
		i = get_index(r->_M_index);
	} catch(gal::error::no_index & e) {
		// if
		//   this does not have an index for the this_process
		// then
		//   register this with this_process
		printv(DEBUG, "managed_object registering\n");
		r->reg(shared_from_this());
		// try again
		i = get_index(r->_M_index);
	}

	return i;
}
gal::object_index		THIS::get_index(gal::process_index p) const
{
	printv_func(DEBUG);
	printv(DEBUG, "  p = %li\n", p);

	long i = p._M_i;

	if(i == -1) {
		//printv(ERROR, "invalid process index\n");
		//throw 0;
	}

	auto it = _M_map_index._M_map.find(p);
	if(it == _M_map_index._M_map.cend()) {
		/// TODO need a good way to suppress this when the throw is going to be caught
		if(0) { 
		printv(WARNING, "process index not found: %li\n", i);
		printv(WARNING, "entries are:\n");
		printv(WARNING, "%16s%16s%16s\n", "proc_idx", "obj_idx.p", "obj_idx.i");
		for(auto e : _M_map_index._M_map) {
			printv(WARNING, "%16li%16li%16li\n",
					e.first._M_i,
					e.second._M_p._M_i,
					e.second._M_i);
		}
		}
		throw gal::error::no_index(__FILE__, __LINE__);
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
	
	std::pair<map_index::map_type::iterator, bool> p =
		_M_map_index._M_map.insert(std::make_pair(i._M_p, i));
	
	if(!p.second) {
		printv(CRITICAL, "not inserted: %li %li\n", i._M_p, i._M_i);
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

	assert(0);
	
	return 0;
}
bool				THIS::has_registry() const
{
	if(_M_registry_parent) return true;
	
	// this could be a registry
	auto r = dynamic_cast<registry_type const * const>(this);
	if(r) {
		//_M_registry_parent = r;
		return true;
	}
	return false;
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

	//printf("before\n");
	//print_index_table();

	if(_M_map_index._M_map.empty()) {
		printv(DEBUG, "index table is empty\n");
	}

	auto it = _M_map_index._M_map.begin();
	while(it != _M_map_index._M_map.end()) {
		auto p = it->first;
		if(p == p_old) {
			printv(DEBUG, "change process index from "
					"%li to %li. object index: %li\n",
					p, p_new, it->second._M_i);

			v.emplace_back(p_new,
					gal::object_index(p_new, it->second._M_i));

			it = _M_map_index._M_map.erase(it);
		} else {
			printv(DEBUG, "DO NOT change process index from "
					"%li to %li. object index: %li\n",
					p, p_new, it->second._M_i);
			it++;
		}
	}

	_M_map_index._M_map.insert(v.begin(), v.end());


	//printf("after\n");
	//print_index_table();

}
void			THIS::load(
		boost::archive::polymorphic_iarchive & ar,
		unsigned int const & version)
{
	printv_func(DEBUG);

	ar & BOOST_SERIALIZATION_NVP(_M_map_index._M_map);
	ar & BOOST_SERIALIZATION_NVP(_M_name);
}
void			THIS::save(
		boost::archive::polymorphic_oarchive & ar,
		unsigned int const & version) const
{
	printv_func(DEBUG);

	ar & BOOST_SERIALIZATION_NVP(_M_map_index._M_map);
	ar & BOOST_SERIALIZATION_NVP(_M_name);
}

void			THIS::print_index_table() const
{
	printf("index table\n");
	printf("    %16s%16s%16s\n", "proc_idx", "obj_idx.p", "obj_idx.i");
	for(auto e : _M_map_index._M_map) {
		printf("    %16li%16li%16li\n",
				e.first._M_i,
				e.second._M_p._M_i,
				e.second._M_i);
	}
}


