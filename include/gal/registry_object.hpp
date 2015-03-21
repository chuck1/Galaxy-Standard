#ifndef GAL_REGISTRY_OBJECT_HPP
#define GAL_REGISTRY_OBJECT_HPP

#include <map>
#include <memory>

#include <gal/decl.hpp>
#include <gal/stl/verbosity.hpp>
#include <gal/registry.hpp>

#include <gal/object_index.hpp>

namespace gal {
	class registry_object:
		public gal::tmp::Verbosity<gal::registry_object>,
		public gal::registry<
				gal::object_index,
				gal::managed_object,
				gal::less_index>	
	{
	public:
		using gal::tmp::Verbosity<gal::registry_object>::printv;

		registry_object()
			//_M_process_index(0),
			//_M_next(0)
		{
			printv_func(DEBUG);
		}
		std::shared_ptr<gal::managed_object>	get(gal::object_index i);
	public:
		void			set_process_index(long int);
		/*
		 * default value is -1
		 */
		long int		_M_process_index;
	};
}

#endif


