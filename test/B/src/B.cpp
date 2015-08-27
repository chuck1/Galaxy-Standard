
#include <boost/serialization/export.hpp>

#include <B.hpp>

void gal::test::B::foo()
{
}

extern "C" gal::test::A* A_create()
{
	return new gal::test::B;
}
extern "C" void A_destroy(gal::test::A* a)
{
	delete a;
}

//BOOST_CLASS_EXPORT_IMPLEMENT(B);

