#ifndef GAL_TMP_WEAK_PTR_HPP
#define GAL_TMP_WEAK_PTR_HPP

#include <memory>
#include <exception>

#include <gal/memory/unique_ptr.hpp>
#include <gal/memory/except.hpp>

namespace gal {
	template<typename T>
	class weak_ptr
	{
	public:
		typedef std::shared_ptr<T>	S;
		typedef gal::unique_ptr<T>	U;
		typedef gal::weak_ptr<T>	W;
		weak_ptr()
		{
		}
		weak_ptr(int)
		{
		}
		weak_ptr(W && w):
			_M_ptr(std::move(w._M_ptr))
		{
		}
		weak_ptr(W const & w):
			_M_ptr(w._M_ptr)
		{
		}
/*		weak_ptr(S const & s):
			_M_ptr(s)
		{
		}*/
		weak_ptr(std::weak_ptr<T> const & w):
			_M_ptr(w)
		{
		}
		weak_ptr(U const & u):
			_M_ptr(u._M_ptr)
		{
		}
		W&		operator=(U const & u)
		{
			_M_ptr = u._M_ptr;
			return *this;
		}
		W&		operator=(W const & w)
		{
			_M_ptr = w._M_ptr;
			return *this;
		}
		T const *	operator->() const
		{
			std::shared_ptr<T> t = _M_ptr.lock();
			if(!t) {
				gal::error::backtrace bt;
				bt.calc();
				throw gal::mem::except::weak_null_pointer(bt);
			} else {
				return t.get();
			}
			return 0;
		}
		T*		operator->()
		{
			std::shared_ptr<T> t = _M_ptr.lock();
			if(!t) {
				gal::error::backtrace bt;
				bt.calc();
				throw gal::mem::except::weak_null_pointer(bt);
			} else {
				return t.get();
			}
			return 0;
		}
		T*		get()
		{
			std::shared_ptr<T> t = _M_ptr.lock();
			if(!t) {
				gal::error::backtrace bt;
				bt.calc();
				throw gal::mem::except::weak_null_pointer(bt);
			} else {
				return t.get();
			}
			return 0;
		}
		T const *	get() const
		{
			std::shared_ptr<T> t = _M_ptr.lock();
			if(!t) {
				gal::error::backtrace bt;
				bt.calc();
				throw gal::mem::except::weak_null_pointer(bt);
			} else {
				return t.get();
			}
			return 0;
		}
		bool			expired() const
		{
			return _M_ptr.expired();
		}
		/** @brief cast */
		template<typename T1>
		gal::weak_ptr<T1>	cast()
		{
			auto s0 = lock();
			auto s1 = std::dynamic_pointer_cast<T1>(s0);
			return gal::weak_ptr<T1>(s1);
		}
		/** @brief conversion */
		template<typename T1>
		operator gal::weak_ptr<T1>()
		{
			auto s = std::dynamic_pointer_cast<T1>(_M_ptr.lock());
			return gal::weak_ptr<T1>(s);
		}
		/** @brief conversion */
		template<typename T1>
		operator gal::weak_ptr<T1>() const
		{
			return gal::weak_ptr<T1>(std::move(
				std::static_pointer_cast<T1>(
					_M_ptr.lock())));
		}
		/** @brief conversion */
		operator std::weak_ptr<T>()
		{
			return _M_ptr;
		}
		/** @brief conversion */
		operator std::shared_ptr<T>()
		{
			return lock();
		}
		/** @brief conversion */
		template<typename T1>
		operator std::weak_ptr<T1>()
		{
			return std::static_pointer_cast<T1>(_M_ptr.lock());
		}
		/** @brief bool conversion */
		operator bool() const
		{
			return (!_M_ptr.expired());
		}
		/** @brief access */
		std::shared_ptr<T>	lock()
		{
			if(_M_ptr.expired()) {
				gal::error::backtrace bt;
				bt.calc();
				throw gal::mem::except::weak_null_pointer(bt);
			}
			return _M_ptr.lock();
		}
	private:
		std::weak_ptr<T>	_M_ptr;
	};
}	

#endif
