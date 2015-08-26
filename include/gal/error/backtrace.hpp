#ifndef GAL_ERROR_BACKTRACE_HPP
#define GAL_ERROR_BACKTRACE_HPP

#include <vector>
#include <string>

namespace gal { namespace error {

	class backtrace
	{
		public:
			backtrace();
			backtrace(backtrace const & bt);
			void		calc();
			void		print() const;
		private:
			std::vector< std::string >	_M_strings;
	};

}}

#endif

