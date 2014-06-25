#ifndef NEBULA_UTIL_COMMAND_SET_HPP
#define NEBULA_UTIL_COMMAND_SET_HPP

#include <map>
#include <string>



namespace gal { namespace std {

	class terminal;
	class command;

	/** @brief %command_set */
	struct command_set {

		typedef ::std::map< ::std::string, ::std::shared_ptr<gal::std::command> >		map_type;

		void			init();
		
		void			list_commands(::std::shared_ptr<gal::std::terminal> term);

		void			operator()(::std::shared_ptr<gal::std::terminal> term, ::std::string str);

		map_type		map_;

	};



}}


#endif





