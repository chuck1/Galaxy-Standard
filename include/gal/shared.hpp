#ifndef GAL_TMP_ESFT_HPP
#define GAL_TMP_ESFT_HPP

#include <cassert>
#include <memory>

namespace gal {
	class shared:
		public std::enable_shared_from_this<gal::shared>
	{
	public:
		virtual ~shared() {};
	};
	template<typename T>
	class enable_shared_from_this:
		virtual public gal::shared
	{
	private:
		typedef std::enable_shared_from_this<gal::shared> ESFT;
	public:
		virtual ~enable_shared_from_this()
		{
		}
		std::shared_ptr<T>	shared_from_this()
		{
			auto s = ESFT::shared_from_this();
			auto t = std::dynamic_pointer_cast<T>(s);
			assert(t);
			return t;
		}
	};
}

#endif


