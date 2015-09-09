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
		virtual public gal::managed_object
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
		void			setParent(T * const & p)
		{
			assert(p);	

			/** TODO need to explain why this was here,
			 * it needs to be removed or changed as
			 * some classes cannot be converted as is
			 */
			//assert(dynamic_cast<gal::object::Child<T>*>(p) != this);
		
			auto r = dynamic_cast<gal::managed_object::registry_type*>(p);
			if(!r) {
				r = p->get_registry();
				if(!r) {
					abort();
				}
			}
			
			gal::managed_object::init(r);

			_M_parent = p;
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

