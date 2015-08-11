#ifndef GAL_STD_NEW_HPP
#define GAL_STD_NEW_HPP

namespace gal {
	class generic_factory {
	public:
		template<typename T>
		T*		new()
		{
			auto vr = _M_vr.lock();
			assert(vr);
			
			T* t = new T;
			t->gal::verb::VerbosityBase::init(vr);
			return t;
		}
	private:
		std::weak_ptr<gal::verb::VerbosityRegistry>	_M_vr;
	};
}

#endif
