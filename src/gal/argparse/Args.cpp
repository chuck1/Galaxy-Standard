/*
#include <gal/argparse/Arg.hpp>
#include <gal/argparse/Args.hpp>
#include <gal/argparse/argparse.hpp>
*/
/*
typedef std::vector< std::string > vec_str;

typedef gal::argparse::Args THIS;

void			THIS::help()
{
	printf("help\n");
}
void			THIS::print()
{
	printf("print\n");
	for(auto p: arg_map_) {
		p.second->print();
	}
}
std::string		THIS::get_value_from_long(std::string l)
{
	for(auto p: arg_map_) {
		Arg_tag* a = dynamic_cast<Arg_tag*>(p.second);

		if(a == NULL) continue;

		if(a->tag_.long_ == l) {
			if(a->values_.empty())
				throw gal::argparse::ValuesEmpty();

			return a->values_.front();
		}
	}

	throw 2;
}
bool			THIS::has_long(std::string l)
{
	for(auto p: arg_map_) {
		Arg_tag* a = dynamic_cast<Arg_tag*>(p.second);

		if(a == NULL) continue;

		if(a->tag_.long_ == l) return true;
	}
	return false;
}
*/
