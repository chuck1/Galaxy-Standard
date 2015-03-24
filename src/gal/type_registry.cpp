#include <gal/type_registry.hpp>

typedef gal::type_registry THIS;

gal::hash_type		THIS::to_hash_code(std::string const & str)
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
std::string			THIS::to_string(gal::hash_type const & hash)
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
	
	auto h = new_index.hash_code();
	auto n = new_index.name();

	map_hash_string_[h] = n;
	map_string_hash_[n] = h;
	
	printv(DEBUG, "%64s%16i\n", n, h);

	//std::cout << new_index.name() << std::endl;
	//std::cout << new_index.hash_code() << std::endl;
}

