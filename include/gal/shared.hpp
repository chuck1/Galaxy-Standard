#ifndef GAL_TMP_ESFT_HPP
#define GAL_TMP_ESFT_HPP

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
	public:
		virtual ~enable_shared_from_this() {}
		std::shared_ptr<T>	shared_from_this()
		{
			return std::dynamic_pointer_cast<T>(std::enable_shared_from_this<gal::shared>::shared_from_this());
		}
	};
}

#endif


