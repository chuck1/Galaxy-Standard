#ifndef GAL_STD_TYPEDEF_HPP
#define GAL_STD_TYPEDEF_HPP

namespace gal {
	struct index
	{
		index():
			_M_p(-1),
			_M_i(0)
		{}
		index(long int i):
			_M_p(-1),
			_M_i(i)
		{}
		index(long int p, long int i):
			_M_p(p),
			_M_i(i)
		{}
		template<typename A>
		void		serialize(A & a, unsigned int const & v)
		{
			a & _M_p;
			a & _M_i;
		}
		long int	_M_p;
		long int	_M_i;
	};
	struct less_index
	{
		bool	operator()(index x, index y)
		{
			if(x._M_p == y._M_p) {
				return x._M_i < y._M_i;
			}
			return x._M_p < y._M_p;
		}
	};
	namespace itf {
		typedef unsigned int			hash_type;
	}
}

#endif
