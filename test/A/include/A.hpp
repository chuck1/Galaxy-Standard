#ifndef A_HPP
#define A_HPP

#include <gal/itf/shared.hpp>

struct A: gal::itf::shared
{
	virtual ~A() {}
	virtual void foo() = 0;
	virtual void release();
};

#endif

