#include <iostream>
using namespace std;

#include <Galaxy-Standard/map.hpp>




class foo: public gal::std::shared {
	public:
		virtual ~foo() {}
};

//template class gal::std::factory<foo>;

//template sp::shared_ptr< gal::std::factory<foo> >	gal::std::factory<foo>::default_factory_;

class bar: public foo {
	public:
		bar() {
			cout << "ctor " << this << endl;
		}
		virtual ~bar() {}
};

int main() {

	gal::std::map<foo> m;

	try {
		auto b1 = std::make_shared<bar>();
		b1->init();
		m.insert(b1);
	} catch(...) {}

	try {
		auto b2 = std::make_shared<bar>();
		//b2->init();
		m.insert(b2);
	} catch(...) {}

	try {
		auto b3 = std::make_shared<bar>();
		b3->init();
		m.insert(b3);
	} catch(...) {}



	m.for_each<0>([] (gal::std::map<foo>::iterator<0> it) {
			cout << it->ptr_->i_ << endl;
			});

}

