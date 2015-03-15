
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

