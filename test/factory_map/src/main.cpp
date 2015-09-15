
#include <gal/stl/factory.hpp> // gal/stl/factory.hpp.in
#include <gal/stl/factory_map.hpp> // gal/stl/factory_map.hpp.in

class foo
{
};
class bar
{
};

int main()
{
	typedef gal::stl::factory_map M;
	
	M m;
	
	auto f = m.find<foo>();
	
	/*	
	auto f = std::make_shared< foo<int> >();

	typedef std::shared_ptr< gal::stl::object__<int> > O;

	O s(f);
	
	m.add<int>(s);
	m.add<int>(1,s);
	
	try {
		m.find<int>();
		printf("m.find<int>() success\n");
	} catch(std::exception & e) {
		printf("m.find<int>() failure\n");
		printf("%s\n", e.what());
	}
	
	try {
		m.find<int>(0);
		printf("m.find<int>(0) success\n");
	} catch(std::exception & e) {
		printf("m.find<int>(0) failure\n");
		printf("%s\n", e.what());
	}

	try {
		m.find<float>();
		printf("m.find<float>() success\n");
	} catch(std::exception & e) {
		printf("m.find<float>() failure\n");
		printf("%s\n", e.what());
	}

	try {
		m.find<int>(1);
		printf("m.find<int>(1) success\n");
	} catch(std::exception & e) {
		printf("m.find<int>(1) failure\n");
		printf("%s\n", e.what());
	}

	return 0;
	*/
	return 1;
}


