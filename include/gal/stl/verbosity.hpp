#ifndef NEB_CORE_ITF_VERBOSITY_HPP
#define NEB_CORE_ITF_VERBOSITY_HPP

#include <map>

namespace gal { namespace tmp {
	/** log levels
	 */
	enum LogLevel
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		CRITICAL
	};
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
		void			printv(
				int sev,
				const char * format, A... a) const
		{
			if(sev >= _M_level) printf(format, a...);
		}
	public:
		static int		_M_level;
	};
	/**
	 * store a register of strings and level pointers for use with config file
	 */
	class VerbosityRegister
	{
	public:
		template<typename T>
		static void	reg(std::string str)
		{
			_M_map[str] = &Verbosity<T>::_M_level;
		}
		static void	set(std::string str, int i)
		{
			auto it = _M_map.find(str);
			if(it == _M_map.end()) return;

			*(it->second) = i;
		}
		static std::map< std::string, int* >	_M_map;
	};
}}

template<typename T> int gal::tmp::Verbosity<T>::_M_level = 1;

#endif
