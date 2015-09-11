#ifndef GAL_VERBOSITY_BASE_HP
#define GAL_VERBOSITY_BASE_HP

#include <assert.h>
#include <memory>

#include <gal/decl.hpp>
#include <gal/verb/decl.hpp>
#include <gal/type_info.hpp>

namespace gal { namespace verb {

	class VerbosityBase:
		virtual public gal::type_info
	{
	public:
		friend class gal::generic_factory;

		typedef gal::verb::Info				I;
		typedef gal::verb::VerbosityRegistry		R;
		typedef std::shared_ptr<R>			S_R;
		typedef std::weak_ptr<R>			W_R;
		typedef std::shared_ptr<I>			S_I;
		typedef std::weak_ptr<I>			W_I;

	protected:
	//private:
		VerbosityBase();
	public:
		VerbosityBase(VerbosityBase && v):
			_M_info_default(std::move(v._M_info_default))
		{
		}
		virtual ~VerbosityBase();
		S_R			get_vr() const;
	protected:
		S_I			_M_info_default;
		W_I			_M_info;
		W_R			_M_reg;
	};

}}

#endif

