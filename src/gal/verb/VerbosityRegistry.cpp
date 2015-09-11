//#include <gal/verb/Verbosity.hpp>
#include <gal/verb/VerbosityRegistry.hpp>

typedef gal::verb::VerbosityRegistry THIS;

THIS::VerbosityRegistry():
	_M_stream(stdout)
{}
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
	printv(DEBUG, "verb set: not registered %s\n", nickname.c_str());
}
THIS::S_I		THIS::get(std::string str)
{
	S_I s(new gal::verb::Info);
	
	auto it = _M_vec.begin();
	while(it != _M_vec.end()) {
		if(std::get<0>(*it) == str) {
			s->_M_level = std::get<2>(*it);
			s->_M_stream = _M_stream;
			return s;
		}
		it++;
	}
	
	printv(CRITICAL, "error: str=%s\n", str.c_str());
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

