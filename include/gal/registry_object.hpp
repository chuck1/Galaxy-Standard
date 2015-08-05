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

		typedef gal::registry<
				gal::object_index,
				gal::managed_object,
				gal::less_index> BASE_REGISTRY;

		registry_object();
		
		registry_object&	operator=(registry_object&& ro)
		{
			BASE_REGISTRY::operator=(std::move(ro));
			return *this;
		}

		//S			get(gal::object_index i);
		
		virtual index_type	first();
		virtual index_type	get_index(S);
		virtual void		set_index(S, index_type);
		/**
		 * overload gal::managed_process::set_index
		 * call set_process_index
		 */
		virtual void		set_index(gal::process_index);

		void			print_table();

	protected:
		/*
		 * insert the indicies of s into this table
		 */
		virtual void		insert(S s);

		void			set_process_index(gal::process_index);
	private:
	};
}

#endif


