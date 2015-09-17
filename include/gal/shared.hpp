#ifndef GAL_TMP_ESFT_HPP
#define GAL_TMP_ESFT_HPP

#include <cassert>
#include <memory>

#include <gal/memory/weak_ptr.hpp>

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
			std::shared_ptr<gal::shared> s;
			try {
				s = ESFT::shared_from_this();
			} catch(std::exception& e) {
				printf("shared_from_this error:\n");
				printf("%s\n", e.what());
				abort();
			}
			std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(s);
			assert(t);
			return t;
		}

		template<typename T2>
		std::shared_ptr<T2>	cast()
		{
			return std::dynamic_pointer_cast<T2>(shared_from_this());
		}

/*		gal::weak_ptr<T>	weak_from_this()
		{
			return gal::weak_ptr<T>(shared_from_this());
		}*/
	};
}

#endif


