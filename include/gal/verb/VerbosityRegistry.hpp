#ifndef NEB_CORE_ITF_VERBOSITY_REGISTER_HPP
#define NEB_CORE_ITF_VERBOSITY_REGISTER_HPP

#include <map>
#include <vector>

#include <gal/decl.hpp>
#include <gal/error/no_index.hpp>

namespace gal { namespace verb {
	/**
	 * store a register of strings and level pointers for use with config file
	 */
	class VerbosityRegistry
		//public gal::verb::Verbosity<gal::tmp::VerbosityRegister>
	{
	public:
		typedef std::tuple<std::string, std::string, int> tuple_type;
		typedef std::vector<tuple_type> vec_type;
	
		template<typename T>
		void			reg(
				std::string nickname,
				int i = INFO)
		{
			std::string str = typeid(T).name();

			_M_vec.insert(_M_vec.end(), tuple_type(str, nickname, i));
			

			if(DEBUG >= my_level()) printf("inserted:\n"
					"\t%s\n"
					"\t%s\n"
					"\t%i\n",
					str.c_str(),
					nickname.c_str(),
					i);
		}
		int			get(
				std::string str);
		void			set(
				std::string nickname,
				int i);
		vec_type		_M_vec;
		
	private:
		/** control verb level of this */
		int			my_level();
		template<typename... Args>
		void			printv(
				int sl,
				char const * fmt,
				Args... args)
		{
			if(sl >= my_level()) {
				printf(fmt, args...);
			}
		}
	};
}}

#endif

