#ifndef GAL_CHILD_HPP
#define GAL_CHILD_HPP

#include <cassert>

namespace gal { namespace stl {

	template<typename T> class child {
		public:
			typedef T parent_t;

			child(): _M_parent(0)
		{
			assert(0);
		}
			child(T* p): _M_parent(p)
		{
			assert(p);
		}

			T* const &	getParent() const
			{
				return _M_parent;
			}
		private:
			T*	_M_parent;
	};

}}

#endif

