#ifndef GAL_ITF_SHARED00_HPP
#define GAL_ITF_SHARED00_HPP

#include <gal/std/decl.hpp>
#include <gal/itf/typedef.hpp>
#include <gal/stl/verbosity.hpp>
#include <gal/shared.hpp>
// gal/itf/shared.hpp
// gal/itf/registry.hpp

namespace gal { namespace itf {
	class no_index:
		public std::exception
	{
		virtual const char * what() const noexcept
		{
			return "no index";
		}
	};
	class shared00:
		public gal::tmp::Verbosity<gal::itf::shared00>,
		virtual public gal::enable_shared_from_this<shared00>
	{
	public:
		shared00();
		virtual ~shared00();
		/*
		 * get index for this process
		 */
		gal::index			get_index() const;
		gal::index			get_index(long int process_index) const;
		//index_type			get_index_creation() const;
		void				set_index(gal::index);
		//void				set_index_creation(gal::index);
		virtual void			register_all(gal::itf::registry * const &);
		gal::itf::registry *		get_registry();
		gal::itf::registry const *	get_registry() const;
		void				change_process_index(
				long int old_pi,
				long int new_pi);
	public:
		/**
		 * used to find the gal::itf::regisry and register this
		 * does not need to be immediate parent
		 * can be any ancestor or at least just not a child
		 */
		gal::itf::shared *		_M_shared_parent;
		/*
		 * index for finding this on this machine
		 */
		//gal::index			_M_index;
		/*
		 * index given to object by creation machine
		 * if not -1, implies that this machine was not the creation
		 * machine and therefore this object was loaded from an
		 * archive
		 */
		//gal::index			_M_index_creation;
		/*
		 * key: process_index
		 * value: object_index
		 *
		 * 'object_index' is the key in the registry map
		 * in process 'process_index'
		 */
		std::map<long int, gal::index>	_M_index_table;
	};
}}

#endif

