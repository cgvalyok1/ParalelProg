#pragma once

template <unsigned n>
class Z
{
	unsigned x;
public:
	Z() { x = 1; }
	Z(unsigned V) :x(V) {}
	Z& operator *=(const Z& N) {
		x = (x*N.x) % n;
		return *this;
	}
	unsigned get() const { return x; }
};