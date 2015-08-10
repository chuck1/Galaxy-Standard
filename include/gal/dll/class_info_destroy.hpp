#ifndef GAL_DLL_CLASS_INFO_DESTROY_HPP
#define GAL_DLL_CLASS_INFO_DESTROY_HPP

#include <dlfcn.h>

#include <memory>
#include <cassert>
#include <string>

#include <gal/typedef.hpp>
#include <gal/decl.hpp>
#include <gal/dll/class_info_destroy_0.hpp>

namespace gal { namespace dll {
	template<class D>
	class class_info_destroy:
		public class_info_destroy_0
	{
	public:
		typedef void(*PD)(D*);
		class_info_destroy(
				std::string n,
				gal::dll::deleter d):
			class_info_destroy_0(d),
			_M_name(n),
			_M_pd(NULL)
		{}
		virtual void	operator()(gal::object::ChildBase * r)
		{
			D* d = dynamic_cast<D*>(r);
			if(!d) {
				abort();
			}
			operator()(d);
		}
		void		open_destroy(void* handle)
		{
			auto name_d = _M_name + "_destroy";

			_M_pd = (PD)dlsym(
					handle,
					name_d.c_str());
			
			if(_M_pd == NULL) {
				//printf("file: %s\n",
				//	filename_.c_str());
				perror(dlerror());
				abort();
			}
		}
		void		operator()(D* d)
		{
			if(_M_pd == NULL) abort();
			_M_pd(d);
		}
	protected:
		std::string	_M_name;
		PD		_M_pd;
	};
}}

#endif

