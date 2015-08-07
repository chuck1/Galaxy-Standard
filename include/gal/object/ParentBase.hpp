#ifndef GAL_OBJECT_PARENT_BASE_HPP
#define GAL_OBJECT_PARENT_BASE_HPP

#include <gal/object/util/decl.hpp>

namespace gal { namespace object {

class ParentBase
{
public
	typedef std::shared_ptr<gal::stl::ChildBase> S;
	
	virtual void	erase(S) = 0;
};
	
}}

#endif


