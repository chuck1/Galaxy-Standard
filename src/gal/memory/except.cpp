#include <gal/memory/except.hpp>


gal::mem::except::weak_null_pointer::weak_null_pointer(gal::error::backtrace const & bt):
	_M_bt(bt)
{
}
char const *	gal::mem::except::weak_null_pointer::what() const noexcept
{
	_M_bt.print();
	return "null pointer exception";
}

