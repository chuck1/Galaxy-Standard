#include <gal/weak_ptr.hpp>

int main()
{

	typedef gal::unique_ptr<int> U;
	typedef gal::weak_ptr<int> W;

	U u0(new int);

	W w0;
	W w1(u0);
	W w2 = u0;
	
	int* i = w0.operator->();
}

