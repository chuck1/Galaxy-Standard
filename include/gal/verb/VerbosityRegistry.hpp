#ifndef NEB_CORE_ITF_VERBOSITY_REGISTER_HPP
#define NEB_CORE_ITF_VERBOSITY_REGISTER_HPP

#include <map>
#include <vector>

#include <gal/decl.hpp>
#include <gal/error/no_index.hpp>
#include <gal/verb/Info.hpp>

namespace gal { namespace verb {


	/**
	 * store a register of strings and level 
	 * pointers for use with config file
	 */
	class VerbosityRegistry
	{
	public:
		typedef std::shared_ptr<gal::verb::Info> S_I;
		typedef std::tuple<
			std::string, 
			std::string, 
			int> TUPLE;
		typedef std::vector<TUPLE> VEC;
	
		VerbosityRegistry();
		template<typename T>
		void			reg(
				std::string nickname,
				int i = INFO)
		{
			std::string str = typeid(T).name();
			
			_M_vec.insert(
					_M_vec.end(),
					TUPLE(str, nickname, i));
			
			printv(
					DEBUG,
					"inserted:\n"
					"\t%s\n"
					"\t%s\n"
					"\t%i\n",
					str.c_str(),
					nickname.c_str(),
					i);
		}
		S_I			get(
				std::string str);
		void			set(
				std::string nickname,
				int i);
		VEC			_M_vec;
		FILE *			_M_stream;
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

