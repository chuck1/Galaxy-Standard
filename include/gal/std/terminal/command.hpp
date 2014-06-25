#ifndef NEBULA_UTIL_COMMAND_HPP
#define NEBULA_UTIL_COMMAND_HPP

#include <boost/program_options.hpp>

namespace bpo = boost::program_options;



namespace gal { namespace std {

	class terminal;

	class command {
		public:
			typedef ::std::shared_ptr<gal::std::terminal>		terminal_type;

			void		operator()(terminal_type term, int ac, char const ** av);

			bpo::options_description						desc_;

			::std::function<void(terminal_type term, bpo::variables_map)>		func_;
	};



}}

#endif
