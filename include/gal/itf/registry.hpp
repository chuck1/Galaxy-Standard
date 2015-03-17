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
		typedef gal::itf::index_type(gal::itf::shared00::*GET_INDEX)() const; // = &gal::itf::shared00::get_index,
		typedef void(gal::itf::shared00::*SET_INDEX)(gal::itf::index_type); // = &gal::itf::shared00::set_index>
		
		GET_INDEX	_M_p_get_index;
		SET_INDEX	_M_p_set_index;

		registry();
		registry(GET_INDEX, SET_INDEX);
		void					reg(std::shared_ptr<gal::itf::shared00> s);
		template<typename B, typename D>
		void					makeDefaultFunc()
		{
			printv_func(DEBUG);
		
			register_type(std::type_index(typeid(B)));
			register_type(std::type_index(typeid(D)));
		
			std::function< std::shared_ptr<B>() > f(
					[]() { return std::shared_ptr<D>(new D(), gal::stl::deleter<D>()); }
					);
		
			gal::stl::factory<B>::default_factory_->template add<D>(f);
		}

	};
}}

#endif

