#ifndef __MYCLASS_H__
#define __MYCLASS_H__

class MyClass {
	public:
		MyClass();
		virtual ~MyClass() {}

		/* use virtual otherwise linker will try to perform static linkage */
		virtual void DoSomething();

	protected:
		int x;
};



#endif

