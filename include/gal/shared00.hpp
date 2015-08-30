#ifndef GAL_ITF_SHARED00_HPP
#define GAL_ITF_SHARED00_HPP

#include <gal/std/decl.hpp>
#include <gal/itf/typedef.hpp>
#include <gal/verb/Verbosity.hpp>
#include <gal/shared.hpp>
#include <gal/mng/index_object.hpp>
// gal/mng/managed_object.hpp
// gal/mng/registry.hpp

namespace gal { namespace itf {
	class shared00:
		public gal::verb::Verbosity<gal::managed_object>,
		virtual public gal::enable_shared_from_this<shared00>
	{
	public:
		shared00();
		virtual ~shared00();
		/*
		 * get index for this process
		 */
		gal::object_index			get_index() const;
		gal::object_index			get_index(long int process_index) const;
		//index_type			get_index_creation() const;
		void				set_index(gal::object_index);
		//void				set_index_creation(gal::object_index);
		virtual void			register_all(gal::registry * const &);
		gal::registry *		get_registry();
		gal::registry const *	get_registry() const;
		void				change_process_index(
				long int old_pi,
				long int new_pi);
	public:
		/**
		 * used to find the gal::itf::regisry and register this
		 * does not need to be immediate parent
		 * can be any ancestor or at least just not a child
		 */
		gal::managed_object *		_M_shared_parent;
		/*
		 * index for finding this on this machine
		 */
		//gal::object_index			_M_index;
		/*
		 * index given to object by creation machine
		 * if not -1, implies that this machine was not the creation
		 * machine and therefore this object was loaded from an
		 * archive
		 */
		//gal::object_index			_M_index_creation;
		/*
		 * key: process_index
		 * value: object_index
		 *
		 * 'object_index' is the key in the registry map
		 * in process 'process_index'
		 */
		std::map<long int, gal::object_index>	_M_index_table;
	};
}}

#endif

