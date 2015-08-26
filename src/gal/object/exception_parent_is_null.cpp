#include <gal/error/backtrace.hpp>

#include <gal/object/child_util/except.hpp>

typedef gal::object::child_util::except::parent_is_null THIS;

THIS::parent_is_null(gal::error::backtrace const & bt):
	_M_bt(bt)
{
}
char const *		THIS::what() const noexcept
{
	_M_bt.print();
	
	return "parent is null";
}

