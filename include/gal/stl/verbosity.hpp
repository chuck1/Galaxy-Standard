#ifndef NEB_CORE_ITF_VERBOSITY_HPP
#define NEB_CORE_ITF_VERBOSITY_HPP

#include <map>

#include <glm/glm.hpp>

#include <gal/etc/print.hpp>

#include <gal/stl/verbosity_base.hpp>
#include <gal/stl/verbosity_register.hpp>

#define printv_func(level) printv(level, "%s\n", __PRETTY_FUNCTION__)

namespace gal { namespace tmp {
	/** log levels
	 */
	/*
	 * the CRTP is used to disambiguate multiple inheritances of this class
	 */
	template<typename T>
	class Verbosity
	{
	protected:
		typedef gal::tmp::VerbosityRegistry VR;
		typedef std::weak_ptr<VR> W_VR;

		int			level() const
		{
			auto r = _M_reg.lock();
			assert(r);
			
			return r->get(typeid(T).name());
		}
		template<typename... A>
		void			printv(
				int sev,
				const char * format, A... a) const
		{
			if(sev >= level())
				printf(format, a...);
		}
		template<typename A>
		void			printv(
				int sev,
				A const & a) const
		{
			if(sev >= level())
				gal::etc::print(a);
		}
	};
}}

//template<typename T> int gal::tmp::Verbosity<T>::_M_level = INFO;

#endif

