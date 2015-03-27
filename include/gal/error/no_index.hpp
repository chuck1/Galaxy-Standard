#ifndef GAL_ERROR_NO_INDEX_HPP
#define GAL_ERROR_NO_INDEX_HPP

#include <string.h>

#include <exception>

namespace gal { namespace error {
	class no_index:
		public std::exception
	{
		virtual const char * what() const noexcept
		{
			return "no index";
		}
	};
	class item_not_found:
		public std::exception
	{
		virtual const char * what() const noexcept
		{
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

