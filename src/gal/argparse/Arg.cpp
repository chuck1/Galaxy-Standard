#include <gal/argparse/Arg.hpp>

gal::argparse::Arg_tag::Arg_tag(Tag t):
	tag_(t)
{
}
std::string	gal::argparse::Arg_tag::name()
{
	if(tag_.short_.empty())
		return tag_.long_;
	else
		return tag_.short_;
}
void		gal::argparse::Arg_tag::print()
{
	printf("name: '%s'\n", name().c_str());
	printf("values:\n");
	for(auto s: values_) {
		std::cout << "\t" << s << std::endl;
	}
}

