#ifndef GAL_TMP_WEAK_PTR_HPP
#define GAL_TMP_WEAK_PTR_HPP

#include <memory>
#include <exception>

namespace gal {
	template<typename T>
	class weak_ptr
	{
	public:
		class null_pointer_exception:
			public std::exception
		{
			virtual char const *	what() const noexcept
			{
				return "null pointer exception";
			}
		};
		typedef std::shared_ptr<T> S;
		typedef gal::weak_ptr<T> W;
		weak_ptr()
		{
		}
		weak_ptr(W && w):
			_M_ptr(std::move(w._M_ptr))
		{
		}
		weak_ptr(S const & s):
			_M_ptr(s)
		{
		}
		W&	operator=(S const & s)
		{
			_M_ptr = s;
			return *this;
		}
		T*	operator->()
		{
			std::shared_ptr<T> t = _M_ptr.lock();
			if(!t) {
				throw null_pointer_exception();
			} else {
				return t.get();
			}
			return 0;
		}
	private:
		weak_ptr(W const & w)
		{
		}
		W&	operator=(W const & w)
		{
			return *this;
		}
	private:
		std::weak_ptr<T>	_M_ptr;
	};
}	

#endif
