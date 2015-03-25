#ifndef GAL_TMP_UNIQUE_PTR_HPP
#define GAL_TMP_UNIQUE_PTR_HPP

#include <memory>
#include <exception>

namespace gal {
	template<typename T> class weak_ptr;

	template<typename T>
	class unique_ptr
	{
	public:
		friend class gal::weak_ptr<T>;
		class null_pointer_exception:
			public std::exception
		{
			virtual char const *	what() const noexcept
			{
				return "null pointer exception";
			}
		};
		typedef std::shared_ptr<T>	S;
		typedef gal::unique_ptr<T>	U;
		typedef gal::weak_ptr<T>	W;
		unique_ptr()
		{
		}
		unique_ptr(U && u):
			_M_ptr(std::move(u._M_ptr))
		{
		}
		unique_ptr(S && s):
			_M_ptr(std::move(s))
		{
		}
		/** downcast move ctor */
		template<typename D>
		unique_ptr(gal::unique_ptr<D> && d):
			_M_ptr(std::move(d._M_ptr))
		{
		}
		unique_ptr(T* && t):
			_M_ptr(std::move(t))
		{
		}
		T *		operator->()
		{
			if(!_M_ptr) {
				throw null_pointer_exception();
			} else {
				return _M_ptr.get();
			}
			return 0;
		}
		T &		operator*()
		{
			if(!_M_ptr) {
				throw null_pointer_exception();
			}
			return *_M_ptr.get();
		}
		T const *	operator->() const
		{
			if(!_M_ptr) {
				throw null_pointer_exception();
			} else {
				return _M_ptr.get();
			}
			return 0;
		}
		long int	use_count() const
		{
			return _M_ptr.use_count();
		}
		operator bool() const
		{
			return bool(_M_ptr);
		}
	private:
		unique_ptr(U const &) = default;
		U&	operator=(U const &) = default;
	private:
		S	_M_ptr;
	};
}	

#endif
