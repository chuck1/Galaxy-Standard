#ifndef GAL_STD_RELEASE_HPP
#define GAL_STD_RELEASE_HPP

#include <boost/signals2.hpp>

// gal/decl.hpp

/** @todo ways to implement hierarchy of calls to base members
 * (ex. when actor is released, we want to call derived member as well as several base class members)
 * 
 * 1. call base class members from inside derived call
 *     bad: lots of extra code in form of calls to base class members
 *          considering number of derived classes there will be, will probably make mistaken
 *          and forget to call a base member somewhere
 * 
 * 2. signals: every base and derived member subscribes to a boost::signal in the top-most class
 *      bad: probably very slow
 *           could forget to connect a method (though less code to maintain than in option 1)
 *
 * 
 * 3. crazy template inheritance (see c-testing/inheritance/multi_virt)
 *     bad: confusing, therefore probably hard to maintain
 *          MULTIPLE INHERITANCE OF DIFFERENT TEMPLATE VERSIONS OF BASE CLASS
 */

#include <gal/shared.hpp>

namespace gal {
	class _release:
		virtual public gal::enable_shared_from_this<gal::_release>
	{
	public:
		typedef std::shared_ptr<gal::_release> S;
		typedef boost::signals2::signal<void(S)> SIGNAL;

		virtual ~_release();
		virtual void			release();
		SIGNAL				sig_release_;
	};
}

#endif


