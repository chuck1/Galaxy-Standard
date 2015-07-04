#ifndef GAL_VERBOSITY_BASE_HP
#define GAL_VERBOSITY_BASE_HP

#include <assert.h>
#include <memory>

#include <gal/decl.hpp>

namespace gal {
	class verbosity_base
	{
	public:
		friend class gal::generic_factory;

		typedef gal::tmp::VerbosityRegistry VR;
		typedef std::weak_ptr<VR>	W_VR;
		typedef std::shared_ptr<VR>	S_VR;
	protected:
	//private:
		verbosity_base();
	public:
		virtual ~verbosity_base();
		void			init(std::shared_ptr<VR> r);
		S_VR			get_vr() const;

		W_VR			_M_reg;
	};
}

#endif

