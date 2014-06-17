
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <Galaxy-Standard/dll/helper.hpp>

#include "myclass.hpp"


using namespace std;

//MyClass*	(*create)();
//void		(*destroy)(MyClass*);

/*
void load(void*& handle,char const * filename) {
	handle = dlopen(filename, RTLD_LAZY);
	if(handle == NULL) {
		cerr << dlerror() << endl;
		exit(0);
	}

	create = (MyClass* (*)())dlsym(handle, "create_object");
	destroy = (void (*)(MyClass*))dlsym(handle, "destroy_object");

	MyClass::create_ = (MyClass* (*)())dlsym(handle, "create_object");

}
*/
int main(int argc, char **argv) {

	// plugin 1
	gal::std::dll::helper<MyClass> h1;
	h1.open("test/dll/sh1/libsh1.so","MyClass");

	gal::std::dll::helper<MyClass> h2;
	h2.open("test/dll/sh2/libsh2.so","MyClass");
	
	MyClass* c1 = h1.create_();
	MyClass* c2 = h2.create_();
	
	c1->DoSomething();
	c2->DoSomething();

	//delete c1;

	h1.destroy_(c1);
	h2.destroy_(c2);
}


