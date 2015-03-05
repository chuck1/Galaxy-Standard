#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>

typedef gal::itf::shared THIS;

gal::itf::shared::shared():
	_M_index(-1),
	_M_shared_parent(0)
{
}
gal::itf::shared::~shared()
{
	//std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
}
std::shared_ptr<gal::itf::registry>		THIS::get_registry()
{
	auto r = std::dynamic_pointer_cast<gal::itf::registry>(shared_from_this());

	if(r) return r;

	auto p = _M_shared_parent;

	assert(p);

	return p->get_registry();
}
void    				        gal::itf::shared::init_shared(gal::itf::shared * const & parent)
{
	std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;

	_M_shared_parent = parent;
		
	// find registry

	auto reg = get_registry();	

	reg->reg(shared_from_this());

	printf("_M_index = %i\n", _M_index);

	assert(_M_index != -1);
}
void						gal::itf::shared::release()
{
}
gal::itf::hash_type				gal::itf::shared::hash_code() const
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::type_index type(typeid(*this));

	//std::cout << type.name() << std::endl;
	//std::cout << type.hash_code() << std::endl;

	return type.hash_code();
}
std::string					gal::itf::shared::name() const
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::type_index type(typeid(*this));

	//std::cout << type.name() << std::endl;
	//std::cout << type.hash_code() << std::endl;

	return type.name();
}
gal::itf::index_type				THIS::get_index() const
{
	return _M_index;
}



gal::itf::hash_type			gal::itf::shared::to_hash_code(std::string const & str)
{
	auto reg = get_registry();

	/// @TODO WTF
	/*
	auto it = reg->map_string_hash_.find(str);
	if(it == reg->map_string_hash_.cend())
	{
		std::cout << std::setw(64) << str << std::endl;

		for(auto p : reg->map_string_hash_)
		{
			std::cout << std::setw(64) << p.first << std::setw(64) << p.second << std::endl;
		}
		throw 0;
	}
	return it->second;*/
	return hash_type();
}
std::string				gal::itf::shared::to_string(gal::itf::hash_type const & hash)
{
	auto reg = get_registry();

	/// @TODO WTF
	/*
	auto it = reg->map_hash_string_.find(hash);
	if(it == reg->map_hash_string_.cend())
	{
		std::cout << std::setw(128) << hash << std::endl;
		for(auto p : reg->map_string_hash_)
		{
			std::cout << std::setw(64) << p.first << std::setw(64) << p.second << std::endl;
		}
		throw 0;
	}
	return it->second;
	*/
	return std::string();
}
void					gal::itf::shared::register_type(std::type_index new_index)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	auto reg = get_registry();
	
	/// @TODO WTF
	/*
	reg->map_hash_string_[new_index.hash_code()] = new_index.name();
	reg->map_string_hash_[new_index.name()] = new_index.hash_code();
	*/

	//std::cout << new_index.name() << std::endl;
	//std::cout << new_index.hash_code() << std::endl;
}
gal::itf::index_type const &		gal::itf::shared::static_get_index(std::shared_ptr<gal::itf::shared> ptr)
{
	assert(ptr);
	return ptr->_M_index;
}



/*
extern gal::itf::registry				gal::itf::shared::registry_;

std::map< gal::itf::hash_type, std::string >		gal::itf::shared::map_hash_string_;
std::map< std::string, gal::itf::hash_type >		gal::itf::shared::map_string_hash_;
*/

