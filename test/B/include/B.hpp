#ifndef B_HPP
#define B_HPP

#include <gal/itf/shared.hpp>

#include <A.hpp>

struct B: A
{
	virtual ~B() {}
	virtual void foo();
};

#endif

