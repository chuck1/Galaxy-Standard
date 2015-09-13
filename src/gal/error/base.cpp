#include <gal/error/base.hpp>

typedef gal::error::base THIS;

char const *		THIS::what() const noexcept
{
	_M_bt.print();

	return  "error";
}


