#include <gal/stl/verbosity_register.hpp>

typedef gal::tmp::VerbosityRegistry THIS;

int			THIS::my_level()
{
	return INFO;
}
void			THIS::set(
		std::string nickname,
		int i)
{
	auto it = _M_vec.begin();
	while(it != _M_vec.end()) {
		if(std::get<1>(*it) == nickname) {
			std::get<2>(*it) = i;
			return;
		}
		it++;
	}
	
	//throw gal::verb::error::not_registered(nickname.c_str());
	if(DEBUG >= my_level()) printf("verb set: not registered %s\n", nickname.c_str());
}
int			THIS::get(std::string str)
{
	auto it = _M_vec.begin();
	while(it != _M_vec.end()) {
		if(std::get<0>(*it) == str) {
			return std::get<2>(*it);
		}
		it++;
	}
	printf("error: str=%s\n", str.c_str());
	throw gal::verb::error::not_registered(str.c_str());
	return 0;
}

/*
   void		THIS::reg(std::string str, int* i)
   {
   auto p = _M_map.insert(value_type(str, i));

   if(!p.second) {
   printv(CRITICAL, "not inserted: %s %p\n",
   str.c_str(), i);
   abort();
   }

   printv(INFO, "inserted: %s %p\n",
   str.c_str(), i);
   }
   void		THIS::set(std::string str, int i)
   {
   auto it = _M_map.find(str);
   if(it == _M_map.end()) {
   printv(ERROR, "no entry: %s\n",
   str.c_str());
   return;
   }

 *(it->second) = i;
 }
 */

