#ifndef GAL_CHILD_HPP
#define GAL_CHILD_HPP

#include <cstdlib>
#include <cassert>
#include <exception>

#include <gal/error/backtrace.hpp>
#include <gal/mng/registry_object.hpp>
#include <gal/object/child_util/except.hpp>

#include <gal/mng/managed_object.hpp>
#include <gal/object/ChildBase.hpp>

namespace gal { namespace object {


	template<typename T>
	class Child:
		virtual public gal::object::ChildBase,
		virtual public gal::mng::managed_object
	{
	public:

		typedef T parent_t;
		/**
		 * exists so you don't have to call every constructor
		 * for every class in a virtual class hierarchy
		 */
		Child(): _M_parent(0)
		{
		}
		Child(T* p): _M_parent(p)
		{
			assert(p);
		}
		virtual void		v_check_delete()
		{
		}
		void			setParent(T * const & p0)
		{
			if(p0 == 0) {
				if(!hasParent())
					assert(p0);
			} else {
				_M_parent = p0;
			}

			/** TODO need to explain why this was here,
			 * it needs to be removed or changed as
			 * some classes cannot be converted as is
			 */
			//assert(dynamic_cast<gal::object::Child<T>*>(p) != this);

			assert(_M_parent);
			T * p = _M_parent;

			auto r = dynamic_cast<gal::mng::managed_object::registry_type*>(p);
			if(!r) {
				r = p->get_registry();
				if(!r) {
					abort();
				}
			}
			
			gal::mng::managed_object::init(r);

		}
		T* const &	getParent() const
		{
			if(_M_parent == 0) {
				gal::error::backtrace bt; bt.calc();
				throw child_util::except::parent_is_null(bt);
			}
			return _M_parent;
		}
		bool		hasParent() const
		{
			return _M_parent != 0;
		}
	private:
		/**
		 * TODO why raw pointer???
		 * why not weak_ptr???
		 */
		T*	_M_parent;
	};

}}

#endif

