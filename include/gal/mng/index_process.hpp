#ifndef GAL_PROCESS_INDEX_HPP
#define GAL_PROCESS_INDEX_HPP

namespace gal {
	struct process_index
	{
		process_index():
			_M_i(-1)
		{}
		process_index(long i):
			_M_i(i)
		{}
		process_index&	operator++(int)
		{
			_M_i++;
			return *this;
		}
		bool		operator==(process_index const & p) const
		{
			return _M_i == p._M_i;
		}
		bool		operator<(process_index const & p) const
		{
			return _M_i < p._M_i;
		}
		template<typename A>
		void		serialize(A & a, unsigned int const & v)
		{
			a & _M_i;
		}
		long 		_M_i;
	};
	struct process_index_less
	{
		bool	operator()(process_index x, process_index y)
		{
			return x._M_i < y._M_i;
		}
	};
}

#endif


