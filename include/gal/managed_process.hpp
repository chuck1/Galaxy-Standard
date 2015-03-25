#ifndef GAL_MANAGED_PROCESS_HPP
#define GAL_MANAGED_PROCESS_HPP

// gal/managed_object.hpp

#include <gal/process_index.hpp>
//#include <gal/registry_object.hpp>
//#include <gal/registry_process.hpp>

namespace gal {
	class managed_process
	{
	public:
		gal::process_index	get_index() const;
		/** overloaded by registry_object */
		virtual void		set_index(gal::process_index);
		
		gal::process_index	_M_index;
	};
}

#endif

