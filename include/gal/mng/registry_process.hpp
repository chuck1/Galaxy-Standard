#ifndef GAL_REGISTRY_PROCESS_HPP
#define GAL_REGISTRY_PROCESS_HPP

#include <map>
#include <memory>

#include <gal/decl.hpp>
#include <gal/verb/Verbosity.hpp>
#include <gal/mng/index_process.hpp>

#include <gal/mng/registry.hpp>
#include <gal/mng/managed_process.hpp>

namespace gal {
	class registry_process:
		virtual public gal::verb::Verbosity<gal::registry_process>,
		virtual public gal::registry<
				gal::process_index,
				gal::managed_process,
				gal::process_index_less>,
		virtual public gal::managed_process
	{
	public:
		using gal::verb::Verbosity<gal::registry_process>::printv;

		//registry_process();

		virtual index_type	first();
		virtual index_type	get_index(S);
		virtual void		set_index(S, index_type);
		virtual void		v_insert(S);

	};
}

#endif


