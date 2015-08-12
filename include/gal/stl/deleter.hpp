#ifndef GAL_DELETER
#define GAL_DELETER

namespace gal { namespace stl {

	template<typename T> struct deleter
	{
		void	operator()(T* p)
		{
			// do not call release here,
			// want to have shared pointer for some release
			// operations. need to make sure release is
			// called before shared pointer is deleted
			//p->release();
			delete p;
		}
	};
}}

#endif
