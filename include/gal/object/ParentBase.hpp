#ifndef GAL_OBJECT_PARENT_BASE_HPP
#define GAL_OBJECT_PARENT_BASE_HPP

#include <memory>

#include <gal/verb/Verbosity.hpp>

#include <gal/object/util/decl.hpp>

namespace gal { namespace object {

class ParentBase:
	virtual public gal::verb::Verbosity<gal::object::ParentBase>
{
public:
	using gal::verb::Verbosity<gal::object::ParentBase>::printv;

	typedef std::shared_ptr<gal::object::ChildBase> S;
	
	//virtual void	erase(S) = 0;
};
	
}}

#endif


