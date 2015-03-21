#ifndef DLL_DELETER_HPP
#define DLL_DELETER_HPP

#include <dlfcn.h>

#include <memory>
#include <cassert>
#include <string>

#include <gal/itf/typedef.hpp>
#include <gal/decl.hpp>
#include <gal/dll/helper_info.hpp>

#include <boost/serialization/nvp.hpp>

namespace gal { namespace dll {
	struct deleter:
		public gal::tmp::Verbosity<gal::dll::deleter>
	{
		public:
			typedef std::function< void(gal::release *) > FUNC;

			deleter(std::shared_ptr<helper_base> h, FUNC f, helper_info hi);
			virtual ~deleter();
			deleter(deleter&& d);
			deleter(deleter const & d);
			helper_info const	getHelperInfo();
			void			operator()(gal::release * p);
		private:
			std::shared_ptr<helper_base>		_M_helper;
			FUNC					_M_delete;
			gal::dll::helper_info			_M_helper_info;
	};
}}

#endif

