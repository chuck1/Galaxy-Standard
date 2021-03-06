#ifndef GAL_OBJECT_CHILD_BASE_HPP
#define GAL_OBJECT_CHILD_BASE_HPP

#include <cstdlib>
#include <cassert>
#include <exception>

#include <gal/object/util/decl.hpp>

#include <gal/mng/registry_object.hpp>

#include <gal/mng/managed_object.hpp>

namespace gal { namespace object {
	
	/**
	 * so neb::fnd0::object::ChildBase::suicide can get parent pointer for any
	 * type
	 */
	class ChildBase
	{
	public:
		typedef std::shared_ptr<gal::object::ParentBase>	S_P;
		typedef std::weak_ptr<gal::object::ParentBase>		W_P;
		
		S_P			get_parent_base();

		virtual void		release() = 0;
	protected:
		W_P			_M_parent_base;
	};
	

}}

#endif

