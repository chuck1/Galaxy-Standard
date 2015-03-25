#ifndef NEB_CORE_ITF_VERBOSITY_HPP
#define NEB_CORE_ITF_VERBOSITY_HPP

#include <map>

#include <glm/glm.hpp>

#include <gal/etc/print.hpp>

#define printv_func(level) printv(level, "%s\n", __PRETTY_FUNCTION__)

enum
{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

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
		Verbosity()
		{
		}
		template<typename... A>
		static void		printv(
				int sev,
				const char * format, A... a)
		{
			if(sev >= _M_level) printf(format, a...);
		}
		template<typename A>
		static void		printv(
				int sev,
				A const & a)
		{
			if(sev >= _M_level) gal::etc::print(a);
		}
	public:
		static int		_M_level;
	};
}}

template<typename T> int gal::tmp::Verbosity<T>::_M_level = INFO;

#endif

