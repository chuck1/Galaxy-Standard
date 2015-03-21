#include <vector>

#include <gal/itf/shared00.hpp>
#include <gal/itf/shared.hpp>

#include <gal/itf/registry00.hpp>

typedef gal::itf::registry00 THIS;

THIS::registry00():
	_M_process_index(0),
	_M_next(0)
{
	printv_func(DEBUG);
}
std::shared_ptr<gal::itf::shared00>		THIS::get(gal::index i)
{
	printv_func(DEBUG);

	auto it = _M_map.find(i);

	if(it == _M_map.cend()) return std::shared_ptr<gal::itf::shared00>();

	return it->second.lock();
}
gal::itf::hash_type				THIS::to_hash_code(std::string const & str)
{
	printv_func(DEBUG);

	auto it = map_string_hash_.find(str);
	if(it == map_string_hash_.cend())
	{
		printv(DEBUG, "%64s\n", str.c_str());

		for(auto p : map_string_hash_)
		{
			printv(DEBUG, "%64i%64s\n", p.second, p.first.c_str());
		}
		throw 0;
	}
	return it->second;
}
std::string					THIS::to_string(gal::itf::hash_type const & hash)
{
	printv_func(DEBUG);
	auto it = map_hash_string_.find(hash);
	if(it == map_hash_string_.cend())
	{
		printv(DEBUG, "%64i\n", hash);
		
		for(auto p : map_hash_string_)
		{
			printv(DEBUG, "%64i%64s\n", p.first, p.second.c_str());
		}
		throw 0;
	}
	return it->second;
}
void				THIS::register_type(std::type_index new_index)
{
	printv_func(DEBUG);

	map_hash_string_[new_index.hash_code()] = new_index.name();
	map_string_hash_[new_index.name()] = new_index.hash_code();

	//std::cout << new_index.name() << std::endl;
	//std::cout << new_index.hash_code() << std::endl;
}
void		THIS::set_process_index(long int p_new)
{
	printv_func(DEBUG);

	long int p_old = _M_process_index;
	
	std::vector< std::pair<gal::index, std::weak_ptr<gal::itf::shared00>> > v;

	auto it = _M_map.begin();
	while(it != _M_map.end()) {
		if(it->first._M_p == p_old) {
			v.emplace_back(gal::index(p_new, it->first._M_i),
					it->second);
			it = _M_map.erase(it);
		} else {
			it++;
		}
	}

	auto it2 = v.begin();
	while(it2 != v.end()) {
		if(it2->second.expired()) {
			it2 = v.erase(it2);
		} else {
			it2->second.lock()->change_process_index(p_old, p_new);
			it2++;
		}
	}
	
	_M_map.insert(v.begin(), v.end());
}







