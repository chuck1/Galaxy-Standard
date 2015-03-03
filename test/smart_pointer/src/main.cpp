#include <gal/weak_ptr.hpp>

int main()
{
	std::shared_ptr<int> s(new int);

	typedef gal::weak_ptr<int> W;

	W w0;
	W w1(s);
	
	int* i = w0.operator->();
}

