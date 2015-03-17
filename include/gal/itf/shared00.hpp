#ifndef GAL_ITF_SHARED00_HPP
#define GAL_ITF_SHARED00_HPP

#include <gal/std/decl.hpp>
#include <gal/itf/typedef.hpp>
#include <gal/stl/verbosity.hpp>
#include <gal/shared.hpp>
// gal/itf/shared.hpp
// gal/itf/registry.hpp

namespace gal { namespace itf {
	class shared00:
		public gal::tmp::Verbosity<gal::itf::shared00>,
		virtual public gal::enable_shared_from_this<shared00>
	{
	public:
		shared00();
		virtual ~shared00();
		index_type			get_index() const;
		index_type			get_index_creation() const;
		void				set_index(index_type);
		void				set_index_creation(index_type);
		virtual void			register_all(gal::itf::registry * const &);
	protected:
		/**
		 * used to find the gal::itf::regisry and register this
		 * does not need to be immediate parent
		 * can be any ancestor or at least just not a child
		 */
		gal::itf::shared *		_M_shared_parent;
		/*
		 * index for finding this on this machine
		 */
		index_type			_M_index;
		/*
		 * index given to object by creation machine
		 * if not -1, implies that this machine was not the creation
		 * machine and therefore this object was loaded from an
		 * archive
		 */
		index_type			_M_index_creation;
	};
}}

#endif

