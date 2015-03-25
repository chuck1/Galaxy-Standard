#ifndef NEB_CORE_ITF_VERBOSITY_REGISTER_HPP
#define NEB_CORE_ITF_VERBOSITY_REGISTER_HPP

#include <map>

#include <gal/stl/verbosity.hpp>

namespace gal { namespace tmp {
	/**
	 * store a register of strings and level pointers for use with config file
	 */
	class VerbosityRegister:
		public gal::tmp::Verbosity<gal::tmp::VerbosityRegister>
	{
	public:
		typedef std::map< std::string, int* > map_type;
		typedef typename map_type::value_type value_type;
		template<typename T>
		void	reg(std::string str)
		{
			_M_map[str] = &Verbosity<T>::_M_level;
		}
		void	reg(std::string str, int*);
		void	set(std::string str, int i);
			_M_map;
	};
}}

#endif

