
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gal/dll/helper.hpp>

#include <A.hpp>

const char * filename = "/home/chuck/git/nebula/external/Galaxy/components/std/test/B/build/dynamic/libB.so";

namespace ba = boost::archive;

int main()
{
	typedef gal::dll::helper<A, std::shared_ptr> H;

	typedef gal::tmp::VerbosityRegistry VR;
	std::shared_ptr<VR> vr(new VR);
	vr->reg<gal::dll::helper_base>("gal dll helper_base");
	vr->reg<gal::managed_object>("gal managed_object");


	std::shared_ptr<H> h(new H(filename));
	h->gal::verbosity_base::init(vr);
	h->open();
	h->add<A>("A");

	auto a0 = h->make_shared<A>();
	auto a1 = h->make_shared<A>();
	
	std::stringstream ss;
	
	// save
	ba::polymorphic_binary_oarchive oar(ss);

	//oar << *a0;
	a0->v_save(oar);

	printf("saved\n");

	// load
	ba::polymorphic_binary_iarchive iar(ss);

	//iar >> *a1;
	a0->v_load(iar);

	printf("loaded\n");

	return 0;
}

