#ifndef GAL_CHILD_UTIL_EXCEPT_HPP
#define GAL_CHILD_UTIL_EXCEPT_HPP

#include <cstdlib>
#include <cassert>
#include <exception>

#include <gal/error/backtrace.hpp>
#include <gal/mng/registry_object.hpp>
#include <gal/mng/managed_object.hpp>

#include<gal/object/ChildBase.hpp>

namespace gal { namespace object { namespace child_util { namespace except {
	
	/**
	 * use only with getParent function
	 */
	class parent_is_null: public std::exception
	{
		public:
			parent_is_null(gal::error::backtrace const &);
			virtual char const *		what() const noexcept;
		private:
			gal::error::backtrace		_M_bt;
	};

}}}}

#endif

