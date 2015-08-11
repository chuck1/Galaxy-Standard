#ifndef NEB_CORE_ITF_VERBOSITY_HPP
#define NEB_CORE_ITF_VERBOSITY_HPP

#include <map>

#include <glm/glm.hpp>

#include <gal/etc/print.hpp>

#include <gal/verb/VerbosityBase.hpp>
#include <gal/verb/VerbosityRegistry.hpp>

#define printv_func(level) printv(level, "%s\n", __PRETTY_FUNCTION__)

namespace gal { namespace verb {
	/** log levels
	 */
	/*
	 * the CRTP is used to disambiguate multiple inheritances of this class
	 *
	 * - every Verbosity<> object must be first initialized with a VR pointer
	 * - do not ues print commands in constructor
	 */
	template<typename T>
	class Verbosity:
		virtual public gal::verb::VerbosityBase
	{
	public:
		typedef gal::verb::VerbosityRegistry VR;
		typedef std::weak_ptr<VR> W_VR;
	protected:
		int			level() const
		{
			auto name = typeid(T).name();

			auto r = get_vr();
			if(!r) {
				return INFO;
			}
			
			return r->get(name);
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

//template<typename T> int gal::verb::Verbosity<T>::_M_level = INFO;

#endif

