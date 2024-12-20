#pragma once
#include <iostream>

class af
{
	unsigned a, b;
public:
	af(){ a = 1; b = 0; }
	af(unsigned aa, unsigned bb) :a(aa), b(bb) {}
	af& operator *= (const af& x)
	{
		a = a * x.a;
		b = a * x.b + b;
		return *this;
	}
	unsigned operator() (unsigned x) const
	{
		return a * x + b;
	}
};

