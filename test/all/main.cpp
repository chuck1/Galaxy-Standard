
#include <Galaxy-Standard/map.hpp>

class foo: public gal::std::shared {
	public:
		virtual ~foo() {}
};

class bar: public foo {
	public:
		virtual ~bar() {}
};

int main() {

	gal::std::map<foo> m;
	
	std::shared_ptr<foo> f(std::make_shared<bar>());
	
	m.insert(f);


}

