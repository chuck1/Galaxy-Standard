#ifndef GAL_VERB_ERROR_HPP
#define GAL_VERB_ERROR_HPP

#include <string.h>
#include <stdio.h>

#include <exception>

namespace gal { namespace verb { namespace error {
	class NotRegistered:
		public std::exception
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

