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
	/**
	 * store a register of strings and level pointers for use with config file
	 */
	class VerbosityRegister:
		public gal::tmp::Verbosity<gal::tmp::VerbosityRegister>
	{
	public:
		template<typename T>
		void	reg(std::string str)
		{
			_M_map[str] = &Verbosity<T>::_M_level;
		}
		void	set(std::string str, int i)
		{
			auto it = _M_map.find(str);
			if(it == _M_map.end()) {
				printv(DEBUG, "no entry: %s\n",
						str.c_str());
				//abort();
				return;
			}

			*(it->second) = i;
		}
		std::map< std::string, int* >	_M_map;
	};
}}

template<typename T> int gal::tmp::Verbosity<T>::_M_level = 1;

#endif
