
#include <gal/std/terminal/terminal.hpp>

int main() {
	
	auto t = sp::make_shared<gal::std::terminal>();
	
	(*t) << "hello " << 3;
	
	t->push('h');
	
	t->enter();



	for(auto l : t->lines_) {
		std::cout << l << std::endl;
	}

}

