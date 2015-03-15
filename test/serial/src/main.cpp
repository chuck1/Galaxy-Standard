
#include <boost/archive/binary_oarchive.hpp>

#include <gal/dll/helper.hpp>

//#include "../external/Galaxy/components/std/test/A/include/A.hpp"
#include <A.hpp>

const char * filename = "/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/std/test/B/build/dynamic/libB.so";

namespace ba = boost::archive;

int main()
{
	typedef gal::dll::helper<A, boost::shared_ptr> H;

	std::shared_ptr<H> h(new H(filename));
	h->open();
	h->add<A>("A");

	auto a = h->make_shared<A>();
	
	std::stringstream ss;

	ba::binary_oarchive oar(ss);
	
	oar << a;
	
}

