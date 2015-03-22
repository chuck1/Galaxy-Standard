#ifndef GAL_ERROR_NO_INDEX_HPP
#define GAL_ERROR_NO_INDEX_HPP

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

#endif

