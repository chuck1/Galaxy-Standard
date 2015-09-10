#ifndef NEB_CORE_ITF_VERBOSITY_HPP
#define NEB_CORE_ITF_VERBOSITY_HPP

#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include <map>

#include <glm/glm.hpp>

#include <gal/etc/print.hpp>

#include <gal/verb/Info.hpp>
#include <gal/verb/VerbosityBase.hpp>
#include <gal/verb/VerbosityRegistry.hpp>

pid_t gettid();

#define printv_func(level) printv(level, "%s\n", __PRETTY_FUNCTION__)

namespace gal { namespace verb {


	/** log levels
	 */
	/*
	 * the CRTP is used to disambiguate multiple 
	 * inheritances of this class
	 *
	 * - every Verbosity<> object must be first 
	 *   initialized with a VR pointer
	 * - do not ues print commands in constructor
	 */
	template<typename T>
	class Verbosity:
		virtual public gal::verb::VerbosityBase
	{
	public:
		typedef gal::verb::VerbosityRegistry		VR;
		typedef std::weak_ptr<VR>			W_VR;
		typedef std::shared_ptr<gal::verb::Info>	S_I;
	protected:
		Verbosity()
		{
			S_I s(new gal::verb::Info);
			s->_M_level = DEBUG;
			s->_M_stream = stdout;
		}
		S_I			level() const
		{
			auto name = typeid(T).name();

			auto r = get_vr();
			if(!r) {
				return _M_info_default;
			}
			
			return r->get(name);
		}
		template<typename... A>
		void			printv(
				int sev,
				const char * format,
				A... a) const
		{
			auto i = level();

			if(sev < i->_M_level) return;

			pid_t tid = gettid();

			fprintf(i->_M_stream, "[%8i]", tid);

			fprintf(i->_M_stream, format, a...);
		}
		template<typename A>
		void			printv(
				int sev,
				A const & a) const
		{
			if(sev >= level())
				gal::etc::print(a);
		}
		S_I			_M_info_default;
	};


}}

//template<typename T> int gal::verb::Verbosity<T>::_M_level = INFO;

#endif

