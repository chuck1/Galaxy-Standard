#ifndef GAL_ITF_REGISTRY_HPP
#define GAL_ITF_REGISTRY_HPP

#include <memory>
#include <map>
#include <typeindex>

#include <gal/std/decl.hpp>
#include <gal/stl/deleter.hpp>
#include <gal/itf/typedef.hpp>
#include <gal/itf/shared00.hpp>
#include <gal/itf/registry00.hpp>

#define CALL_MEMBER_FN(object,ptrToMember) ((object).*(ptrToMember))

namespace gal { namespace itf {
	class registry:
		public gal::itf::registry00
	{
	public:
		//typedef gal::index(gal::itf::shared00::*GET_INDEX)() const;
		// = &gal::itf::shared00::get_index,
		//typedef void(gal::itf::shared00::*SET_INDEX)(gal::index);
		// = &gal::itf::shared00::set_index>
		
	private:
		//GET_INDEX	_M_p_get_index;
		//SET_INDEX	_M_p_set_index;

	};
}}

#endif

