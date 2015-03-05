#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>

typedef gal::itf::registry THIS;

THIS::registry(): next_(0)
{
	std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
}
void                                            THIS::reg(std::shared_ptr<gal::itf::shared> s)
{
	std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
	//std::cout << __PRETTY_FUNCTION__ << " s=" << s.get() << std::endl;

	if(s->_M_index == -1) {
		printf("assign index %i\n", next_);

		s->_M_index = next_++;
	}

	map_[s->_M_index] = s;
}
std::shared_ptr<gal::itf::shared>		THIS::get(gal::itf::index_type i)
{
	auto it = map_.find(i);

	if(it == map_.cend()) return std::shared_ptr<gal::itf::shared>();

	return it->second.lock();
}
gal::itf::hash_type				THIS::to_hash_code(std::string const & str)
{
	auto it = map_string_hash_.find(str);
	if(it == map_string_hash_.cend())
	{
		std::cout << std::setw(64) << str << std::endl;

		for(auto p : map_string_hash_)
		{
			std::cout << std::setw(64) << p.first << std::setw(64) << p.second << std::endl;
		}
		throw 0;
	}
	return it->second;
}
std::string					THIS::to_string(gal::itf::hash_type const & hash)
{
	auto it = map_hash_string_.find(hash);
	if(it == map_hash_string_.cend())
	{
		std::cout << std::setw(128) << hash << std::endl;
		for(auto p : map_string_hash_)
		{
			std::cout << std::setw(64) << p.first << std::setw(64) << p.second << std::endl;
		}
		throw 0;
	}
	return it->second;
}
void						THIS::register_type(std::type_index new_index)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	map_hash_string_[new_index.hash_code()] = new_index.name();
	map_string_hash_[new_index.name()] = new_index.hash_code();

	//std::cout << new_index.name() << std::endl;
	//std::cout << new_index.hash_code() << std::endl;
}




