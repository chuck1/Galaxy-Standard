#ifndef DLL_DELETER_HPP
#define DLL_DELETER_HPP

#include <dlfcn.h>

#include <memory>
#include <cassert>
#include <string>

#include <gal/typedef.hpp>
#include <gal/decl.hpp>
#include <gal/dll/helper_info.hpp>

#include <boost/serialization/nvp.hpp>

namespace gal { namespace dll {
	struct deleter:
		public gal::tmp::Verbosity<gal::dll::deleter>
	{
		public:
			typedef std::shared_ptr<gal::dll::class_info_destroy_0> S_C;
			typedef std::function<void(S_C, gal::_release *)> FUNC;

			deleter(
					std::shared_ptr<helper_base> h,
					FUNC f,
					helper_info hi,
					S_C c);
			virtual ~deleter();
			deleter(deleter&& d);
			deleter(deleter const & d);
			helper_info const	getHelperInfo();
			void			operator()(gal::_release * p);
		//private:
			std::shared_ptr<helper_base>		_M_helper;
			FUNC					_M_delete;
			gal::dll::helper_info			_M_helper_info;
			S_C					_M_class_info;
	};
}}

#endif

