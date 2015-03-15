
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gal/dll/helper.hpp>

//#include "../external/Galaxy/components/std/test/A/include/A.hpp"
#include <A.hpp>

const char * filename = "/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/std/test/B/build/dynamic/libB.so";

namespace ba = boost::archive;

int main()
{
	typedef gal::dll::helper<A, std::shared_ptr> H;

	std::shared_ptr<H> h(new H(filename));
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

