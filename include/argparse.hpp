#ifndef ARGPARSE_HPP
#define ARGPARSE_HPP

#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

typedef std::vector< std::string > vec_str;

struct Tag
{
	Tag(std::string w)
	{
		if(w[1] == '-')
		{
			assert(w.size() > 2);
			long_ = w.substr(2);
		}
		else
		{
			assert(w.size() > 1);
			short_ = w.substr(1);
		}
	}

	std::string	short_;
	std::string	long_;
};

struct Arg
{
	virtual std::string	name() = 0;
	virtual void		print() = 0;
	vec_str			values_;
};

struct Arg_tag: Arg
{
	Arg_tag(Tag t): tag_(t) {}
	// -a --apple
	Tag	tag_;
	virtual std::string	name()
	{
		if(tag_.short_.empty())
			return tag_.long_;
		else
			return tag_.short_;
	}
	virtual void		print()
	{
		std::cout << "'" << name() << "'" << std::endl;
		for(auto s: values_) {
			std::cout << "\t" << s << std::endl;
		}
	}
};

struct Arg_positional: Arg
{
	// file
	std::string	name_;
};


struct Args
{
	void	help()
	{
	}
	void	print()
	{
		for(auto p: arg_map_) {
			p.second->print();
		}
	}
	std::string	get_value_from_long(std::string l)
	{
		for(auto p: arg_map_) {
			Arg_tag* a = dynamic_cast<Arg_tag*>(p.second);

			if(a == NULL) continue;

			if(a->tag_.long_ == l) {
				if(a->values_.empty())
					throw 1;
				
				return a->values_.front();
			}
		}

		throw 2;
	}
	
	
	std::map< std::string, Arg* >	arg_map_;
};



Arg*	make_arg(vec_str words)
{
	std::cout << "make_arg" << std::endl;
	for(auto w : words)
		std::cout << "'" << w << "'" << std::endl;

	assert(!words.empty());

	if(words[0][0] == '-')
	{
		Tag t(words[0]);
		Arg_tag* a = new Arg_tag(t);
		
		for(unsigned int i = 1; i < words.size(); i++) {
			a->values_.push_back(words[i]);
		}

		return a;
	}

	assert(0);
	return 0;
}

Args Parse(int ac, char ** av, char const * format)
{
	vec_str words;

	Args ret;

	char * buf = new char[strlen(format)+1];
	strcpy(buf, format);

	char * c = buf;
	char * head = buf;
	for(; c < (buf + strlen(format) + 1); c++)
	{
		//std::cout << *c << std::endl;
		if(*c == ' ' || *c == 0)
		{
			*c = 0;
			words.push_back(head);
			head = c+1;
		}
	}
	//for(auto w : words)
	//std::cout << w << std::endl;

	vec_str temp;
	for(unsigned int i = 0; i < words.size(); i++)
	{
		if(words[i][0] == '-')
		{
			//std::cout << "tag " << words[i] << std::endl;
			if(temp.empty()) temp.push_back(words[i]);
			else {
				Arg* a = make_arg(temp);
				ret.arg_map_[a->name()] = a;
				temp.clear();
				temp.push_back(words[i]);
			}
		}
		else
		{
			temp.push_back(words[i]);
		}
	}

	if(!temp.empty())
	{
		Arg* a = make_arg(temp);
		ret.arg_map_[a->name()] = a;
	}

	ret.help();
	ret.print();

	return ret;
};

#endif
