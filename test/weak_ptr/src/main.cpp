
#include <gal/memory/weak_ptr.hpp>

struct bar
{
};

struct foo: bar
{
};

typedef gal::weak_ptr<foo> W_F;
typedef gal::weak_ptr<bar> W_B;

void fun(W_B w)
{
	
}

int main()
{
	std::shared_ptr<foo> sf;
	std::shared_ptr<bar> sb;
	
	W_F f0;

	W_B b0;
	W_B b1(sb);
	//W_B b2(std::move(sb));
	W_B b3(sf);
	//W_B b4(std::move(sf));
	
	fun(f0);

	return 0;
}



