#ifndef GAL_VERBOSITY_BASE_HP
#define GAL_VERBOSITY_BASE_HP

#include <assert.h>
#include <memory>

#include <gal/decl.hpp>
#include <gal/verb/decl.hpp>

namespace gal { namespace verb {

	class VerbosityBase
	{
	public:
		friend class gal::generic_factory;

		typedef gal::verb::VerbosityRegistry VR;
		typedef std::weak_ptr<VR>	W_VR;
		typedef std::shared_ptr<VR>	S_VR;
	protected:
	//private:
		VerbosityBase();
	public:
		virtual ~VerbosityBase();
		void			init(std::shared_ptr<VR> r);
		S_VR			get_vr() const;

		W_VR			_M_reg;
	};

}}

#endif

