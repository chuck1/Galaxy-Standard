#ifndef GAL_CHILD_HPP
#define GAL_CHILD_HPP

#include <cstdlib>
#include <cassert>
#include <exception>

#include <gal/registry_object.hpp>

#include <gal/managed_object.hpp>

namespace gal { namespace stl {
	namespace child_util {
		/**
		 * use only with getParent function
		 */
		class exception_parent_is_null: public std::exception
		{
		};
	}

	template<typename T>
	class child:
		virtual public gal::managed_object
	{
	public:

		typedef T parent_t;
		/**
		 * exists so you don't have to call every constructor
		 * for every class in a virtual class hierarchy
		 */
		child(): _M_parent(0)
		{
		}
		child(T* p): _M_parent(p)
		{
			assert(p);
		}
		void		setParent(T * const & p)
		{
			assert(p);	

			/** TODO need to explain why this was here,
			 * it needs to be removed or changed as
			 * some classes cannot be converted as is
			 */
			//assert(dynamic_cast<gal::stl::child<T>*>(p) != this);
		
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
				throw child_util::exception_parent_is_null();
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

