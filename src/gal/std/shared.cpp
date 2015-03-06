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
gal::itf::registry*				THIS::get_registry()
{
	auto r = dynamic_cast<gal::itf::registry*>(this);

	if(r) return r;

	auto p = _M_shared_parent;

	assert(p);

	return p->get_registry();
}
void    				        THIS::init_shared(THIS * const & parent)
{
	std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;

	_M_shared_parent = parent;
		
	// find registry

	auto reg = get_registry();	

	reg->reg(shared_from_this());

	printf("_M_index = %i\n", _M_index);

	assert(_M_index != -1);
}
void						THIS::release()
{
}
gal::itf::hash_type				THIS::hash_code() const
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::type_index type(typeid(*this));

	//std::cout << type.name() << std::endl;
	//std::cout << type.hash_code() << std::endl;

	return type.hash_code();
}
std::string					THIS::name() const
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
gal::itf::index_type const &			THIS::static_get_index(std::shared_ptr<THIS> ptr)
{
	assert(ptr);
	return ptr->_M_index;
}


