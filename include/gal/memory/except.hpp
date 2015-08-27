
#ifndef GAL_MEM_EXCEPT_HPP
#define GAL_MEM_EXCEPT_HPP

#include <exception>

#include <gal/error/backtrace.hpp>

namespace gal { namespace mem { namespace except {


	class weak_null_pointer:
		public std::exception
	{
	public:
		weak_null_pointer(gal::error::backtrace const &);
		virtual char const *		what() const noexcept;
	private:
		gal::error::backtrace		_M_bt;
	};


}}}

#endif

