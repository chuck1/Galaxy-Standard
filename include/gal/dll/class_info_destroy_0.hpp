#ifndef GAL_CLASS_INFO_DESTROY_0_HPP
#define GAL_CLASS_INFO_DESTROY_0_HPP

#include <gal/typedef.hpp>
#include <gal/dll/deleter.hpp>

namespace gal { namespace dll {
	class class_info_destroy_0
	{
	public:
		class_info_destroy_0(gal::dll::deleter d):
			_M_del(d)
		{}
		virtual void	operator()(gal::_release *) = 0;
		gal::dll::deleter	_M_del;
	};
}}

#endif

