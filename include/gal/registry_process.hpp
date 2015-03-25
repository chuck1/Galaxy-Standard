#ifndef GAL_REGISTRY_PROCESS_HPP
#define GAL_REGISTRY_PROCESS_HPP

#include <map>
#include <memory>

#include <gal/decl.hpp>
#include <gal/stl/verbosity.hpp>
#include <gal/process_index.hpp>

#include <gal/registry.hpp>
#include <gal/managed_process.hpp>

namespace gal {
	class registry_process:
		public gal::tmp::Verbosity<gal::registry_process>,
		public gal::registry<
				gal::process_index,
				gal::managed_process,
				gal::process_index_less>,
		public gal::managed_process
	{
	public:
		using gal::tmp::Verbosity<gal::registry_process>::printv;

		//registry_process();

		virtual index_type	first();
		virtual index_type	get_index(S);
		virtual void		set_index(S, index_type);
		virtual void		insert(S);

	};
}

#endif

