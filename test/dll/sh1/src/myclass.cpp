

#include <iostream>


#include "../../prog/src/myclass.hpp"

using namespace std;



extern "C" MyClass* MyClass_create()
{
	  return new MyClass;
}

extern "C" void MyClass_destroy( MyClass* object )
{
	  delete object;
}

MyClass::MyClass()
{
	  x = 40;
}

void MyClass::DoSomething()
{
	  cout<< x <<endl;
}


