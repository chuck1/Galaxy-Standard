#include <gal/argparse/Tag.hpp>
#include <gal/argparse/Arg.hpp>
#include <gal/argparse/argparse.hpp>

gal::argparse::Arg*		gal::argparse::make_arg(vec_str words)
{
	//printv(DEBUG, "make_arg");

	for(auto w : words)
		//printv(DEBUG, "    '%s'\n", w.c_str());

	assert(!words.empty());

	if(words[0][0] == '-')
	{
		Tag t(words[0]);
		Arg_tag* a = new Arg_tag(t);
		
		for(unsigned int i = 1; i < words.size(); i++) {
			a->values_.push_back(words[i]);
		}

		return a;
	} else {
		return 0;
	}
	
	return 0;
}
vec_str				gal::argparse::split(char * str)
{
	char * buf = new char[strlen(str)+1];
	char * c = buf;
	char * head = buf;
	vec_str words;

	strcpy(buf, str);

	// split words by spaces
	for(; c < (buf + strlen(buf) + 1); c++)
	{
		//std::cout << *c << std::endl;
		if(*c == ' ' || *c == 0)
		{
			*c = 0;
			words.push_back(head);
			head = c+1;
		}
	}
	for(auto w : words) {
		//printv(DEBUG, "'%s'", w.c_str());
	}

	return words;
}
vec_str			gal::argparse::split(int ac, char ** av)
{
	vec_str words;

	//auto words = split(format);

	for(int i = 0; i < ac; i++) {
		auto temp = split(av[i]);
		words.insert(
				words.end(),
				std::make_move_iterator(temp.begin()),
				std::make_move_iterator(temp.end())
			    );
	}

	return words;
}

