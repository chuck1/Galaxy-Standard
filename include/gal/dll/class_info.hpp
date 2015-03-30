#ifndef GAL_DLL_CLASS_INFO_HPP
#define GAL_DLL_CLASS_INFO_HPP

#include <dlfcn.h>

#include <memory>
#include <cassert>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/serialization/nvp.hpp>

#include <gal/typedef.hpp>

#include <gal/decl.hpp>
#include <gal/shared.hpp>
#include <gal/dll/class_info_destroy.hpp>

namespace gal { namespace dll {
	template<class D, typename... ARGS>
	class class_info: public class_info_destroy<D>
	{
	public:
		typedef D*(*PC)(ARGS...);

		using class_info_destroy<D>::open_destroy;
		using class_info_destroy<D>::_M_name;

		class_info(
				std::string n,
				gal::dll::deleter d):
			class_info_destroy<D>(n, d),
			_M_pc(NULL)
		{}
		void		open(void* handle)
		{
			open_destroy(handle);

			auto name_c = _M_name + "_create";

			_M_pc = (PC)dlsym(
					handle,
					name_c.c_str());

			if(_M_pc == NULL) {
				//printf("file: %s\n",
				//	filename_.c_str());
				perror(dlerror());
				abort();
			}
		}
		D*		operator()(ARGS... a)
		{
			if(_M_pc == NULL) abort();
			return _M_pc(a...);
		}
	private:
		PC		_M_pc;
	};
}}

#endif

