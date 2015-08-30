
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gal/dll/helper.hpp>

#include <gal/stl/map.hpp>
#include <gal/mng/registry_object.hpp>
#include <gal/mng/registry_process.hpp>
#include <gal/verb/VerbosityRegistry.hpp>

namespace ba = boost::archive;

struct foo: gal::managed_object
{
	virtual void	release()
	{
	}
};

struct bar: gal::managed_process
{
	virtual void	release()
	{
	}
};

int main()
{
	try {

	std::shared_ptr<gal::verb::VerbosityRegistry> vr(
			new gal::verb::VerbosityRegistry);
	
	vr->reg<gal::managed_process>("gal managed_process");
	vr->reg<gal::managed_object>("gal managed_object");
	vr->reg<gal::registry_base>("gal registry_base");
	vr->reg<gal::registry_process>("gal registry_process");
	vr->reg<gal::registry_object>("gal registry_object");
	
	typedef gal::registry_object R1;
	typedef std::shared_ptr<R1> S_R1;
	
	typedef gal::registry_process R0;
	typedef std::shared_ptr<R0> S_R0;
	
	// process registry
	S_R0 r0(new R0);

	r0->gal::verb::VerbosityBase::init(vr);
	r0->init();
	
	// object registry
	S_R1 r1(new R1);
	r1->gal::verb::VerbosityBase::init(vr);

	r0->reg(r1);

	r1->init();


	typedef std::shared_ptr<foo> S_F;


	S_F f0(new foo);
	S_F f1(new foo);
	S_F f2(new foo);

	f0->gal::verb::VerbosityBase::init(vr);
	f1->gal::verb::VerbosityBase::init(vr);
	f2->gal::verb::VerbosityBase::init(vr);

	r1->reg(f0);
	r1->reg(f1);
	r1->reg(f2);

	gal::object_index i0 = f0->get_index();

	r1->get(i0);

	} catch(std::exception & e) {
	
	printf("%s\n", e.what());

	}
}

