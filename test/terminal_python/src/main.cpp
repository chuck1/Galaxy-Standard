
#include <gal/std/terminal/python.hpp>

int main() {
	
	auto t = sp::make_shared<gal::std::term::python>();
	
	t->init();
	
	t->push('h');
	
	t->enter();
	
	
	
	for(auto l : t->lines_) {
		std::cout << l << std::endl;
	}

}

