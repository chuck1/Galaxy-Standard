
#include <gal/stl/object_map.hpp> // gal/stl/object_map.hpp.in

template<typename... A>
class foo:
	public gal::stl::object__<A...>
{
public:
	virtual ~foo()
	{
	}
};

int main()
{
	typedef gal::stl::object_map<int> M;
	
	M m;
	
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
}


