#ifndef GAL_ERROR_NO_INDEX_HPP
#define GAL_ERROR_NO_INDEX_HPP

#include <string.h>
#include <stdio.h>

#include <exception>

#include <gal/error/base.hpp>

namespace gal { namespace error {


	class no_index:
		public std::exception
	{
	public:
		no_index(const char * file, int line):
			_M_file(file),
			_M_line(line)
		{
			sprintf(buffer, "%s:%i: no index", _M_file, _M_line);
		}
		virtual const char * what() const noexcept
		{
			return buffer;
		}
		const char *	_M_file;
		int		_M_line;
		char		buffer[128];
	};
	class item_not_found:
		public gal::error::base
	{
	public:
		item_not_found(gal::error::backtrace const & bt):
			gal::error::base(bt)
		{
		}
		virtual const char * what() const noexcept
		{
			_M_bt.print();
			return "item not found";
		}
	};
}}
namespace gal { namespace verb { namespace error {
	class not_registered
	{
	public:
		not_registered(const char * s)
		{
			strcpy(buffer, "verbosity not registered ");
			strcat(buffer, s);
		}
		virtual const char * what() const noexcept
		{
			return buffer;
		}
		char		buffer[128];
	};
}}}

#endif

