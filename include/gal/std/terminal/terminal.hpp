#ifndef NEBULA_UTIL_TERMINAL_HPP
#define NEBULA_UTIL_TERMINAL_HPP

#include <string>
#include <deque>
#include <sstream>

#include <gal/std/shared.hpp>


namespace gal { namespace std {

	class command_set;

	class __terminal_data: virtual public gal::std::shared {
		public:
			::std::deque< ::std::string >			lines_;
			::std::stringstream				ss_;
	};

	/** @brief temporary stringstream */
	struct stringstream {
		stringstream(sp::shared_ptr<gal::std::__terminal_data> t);
		stringstream(stringstream&& ss);
		~stringstream();
		template<typename T> stringstream		operator<<(T const & t) {
			assert(t_);
			t_->ss_ << t;
			return ::std::move(*this);
		}
		sp::shared_ptr<gal::std::__terminal_data>		t_;
	};

	/** @brief terminal */
	class terminal: virtual public gal::std::__terminal_data {
		public:
			terminal();
			
			/** @brief push formatted text into terminal history */
			template<typename T> gal::std::stringstream		operator<<(T const & t) {
				gal::std::stringstream ss(sp::dynamic_pointer_cast<gal::std::terminal>(shared_from_this()));
				return ::std::move(ss << t);
			}
			/** @brief push character onto current line */
			void							push(char c);
			virtual void						eval(::std::string const & s);
			void							enter();


			/** @brief %command_set
			 *
			 * @note WEAK
			 */
			sp::shared_ptr<gal::std::command_set>		cs_;


			unsigned int					lines_max_;

			::std::string					line_;
			::std::string					prompt_end_;
			

	};

}}

#endif
