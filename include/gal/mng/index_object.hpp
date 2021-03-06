#ifndef GAL_OBJECT_INDEX_HPP
#define GAL_OBJECT_INDEX_HPP

#include <gal/mng/index_process.hpp>

namespace gal {
	struct object_index
	{
		object_index();
		object_index(long int i);
		object_index(gal::process_index p, long int i);
		object_index&	operator++(int);
		template<typename A>
		void		serialize(A & a, unsigned int const & v)
		{
			a & _M_p;
			a & _M_i;
		}
		gal::process_index	_M_p;
		long int		_M_i;
	};
	struct less_index
	{
		bool	operator()(object_index x, object_index y)
		{
			if(x._M_p == y._M_p) {
				return x._M_i < y._M_i;
			}
			return x._M_p < y._M_p;
		}
	};
}

#endif

