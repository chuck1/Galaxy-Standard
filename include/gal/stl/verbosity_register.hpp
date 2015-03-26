#ifndef NEB_CORE_ITF_VERBOSITY_REGISTER_HPP
#define NEB_CORE_ITF_VERBOSITY_REGISTER_HPP

#include <map>
#include <vector>

#include <gal/decl.hpp>

namespace gal { namespace tmp {
	/**
	 * store a register of strings and level pointers for use with config file
	 */
	class VerbosityRegistry
		//public gal::tmp::Verbosity<gal::tmp::VerbosityRegister>
	{
	public:
		typedef std::tuple<std::string, std::string, int> tuple_type;
		typedef std::vector<tuple_type> vec_type;
	
		int			get(std::string str)
		{
			auto it = _M_vec.begin();
			while(it != _M_vec.end()) {
				if(std::get<0>(*it) == str) {
					return std::get<2>(*it);
				}
			}
			abort();
			return 0;
		}
		template<typename T>
		void			reg(
				std::string nickname,
				int i = INFO)
		{
			std::string str = typeid(T).name();

			_M_vec.insert(_M_vec.end(), tuple_type(str, nickname, i));
	
			printf("inserted:\n"
					"\t%s\n"
					"\t%s\n"
					"\t%i\n",
					str.c_str(), i);
		}
		void			set(
				std::string nickname,
				int i)
		{
			auto it = _M_vec.begin();
			while(it != _M_vec.end()) {
				if(std::get<1>(*it) == nickname) {
					std::get<2>(*it) = i;
					return;
				}
			}
			abort();
		}
		vec_type	_M_vec;
	};
}}

#endif

