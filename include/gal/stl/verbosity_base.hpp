#ifndef GAL_VERBOSITY_BASE_HP
#define GAL_VERBOSITY_BASE_HP

#include <assert.h>
#include <memory>

#include <gal/decl.hpp>

namespace gal {
	class verbosity_base
	{
	public:
		typedef gal::tmp::VerbosityRegistry VR;
		typedef std::weak_ptr<VR> W_VR;

		virtual ~verbosity_base() {}
		void			init(std::shared_ptr<VR> r)
		{
			assert(r);
			_M_reg = r;
		}

		W_VR			_M_reg;
	};
}

#endif

