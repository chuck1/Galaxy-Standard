
#include <boost/serialization/export.hpp>

#include <B.hpp>

void B::foo()
{
}

extern "C" A* A_create()
{
	return new B;
}
extern "C" void A_destroy(A* a)
{
	delete a;
}

//BOOST_CLASS_EXPORT_IMPLEMENT(B);

