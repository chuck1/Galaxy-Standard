#ifndef GAL_REGISTRY_OBJECT_HPP
#define GAL_REGISTRY_OBJECT_HPP

#include <map>
#include <memory>

#include <gal/decl.hpp>
#include <gal/stl/verbosity.hpp>
#include <gal/object_index.hpp>

#include <gal/registry.hpp>
#include <gal/managed_process.hpp>

namespace gal {
	class registry_object:
		virtual public gal::tmp::Verbosity<gal::registry_object>,
		virtual public gal::registry<
				gal::object_index,
				gal::managed_object,
				gal::less_index>,
		virtual public gal::managed_process
	{
	public:
		using gal::tmp::Verbosity<gal::registry_object>::printv;

		registry_object();

		//S			get(gal::object_index i);
		
		virtual index_type	first();
		virtual index_type	get_index(S);
		virtual void		set_index(S, index_type);
		virtual void		insert(S);
	
		/**
		 * overload gal::managed_process::set_index
		 * call set_process_index
		 */
		virtual void		set_index(gal::process_index);
			
		void			set_process_index(gal::process_index);
	};
}

#endif


