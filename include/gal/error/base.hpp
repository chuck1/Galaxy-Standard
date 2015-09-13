#ifndef GAL_ERROR_BASE_HPP
#define GAL_ERROR_BASE_HPP

#include <string.h>
#include <stdio.h>

#include <exception>

#include <gal/error/backtrace.hpp>

namespace gal { namespace error {
	class base:
		public std::exception
	{
	public:
		base(gal::error::backtrace const & bt):
			_M_bt(bt)
		{}
		char const *		what() const noexcept;
		gal::error::backtrace	_M_bt;
	};
}}

#endif

