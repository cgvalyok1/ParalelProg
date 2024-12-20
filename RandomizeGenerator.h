#pragma once
#include <iostream>
#include <concepts>
#include <type_traits>
#include "af.h"
#include <num_threads.h>

template <class T> concept monoid = requires (T x) { T(); x *= x; };
template <monoid T, std::unsigned_integral U>
T power(T x, U n) {

	auto r = T();
	while (n > 0) {
		if (n & 1 != 0) {
			r *= x;
		}
		x *= x;
		n >>= 1;
	}
	return r;
}

template <class F> requires std::invocable<F, unsigned>
void affine_transform(unsigned aa, unsigned bb, F map, unsigned* v, size_t n, unsigned x0) {
	unsigned T = get_num_threads();
	std::vector <std::thread> w(T - 1);
	auto worker = [v, aa, bb, map, n, x0, T](unsigned t) {
		unsigned s, b, e;
		s = n / T;
		b = n % T;
		if (t < b)
			b = 1 + s * t;
		else
			b += s * t;
		e = b + s;
		af gen(aa, bb);
		for (size_t i = b; i < e; i++) {
			v[i] = map(power(gen, i)(x0));
		}
	};

	for (unsigned t = 1; t < T; t++) {
		w.emplace_back(worker, t);
	}
	worker(0);
	for (auto& thr : w)
	{
		if (thr.joinable())
		{
			thr.join();
		}
	}
}
// x0 = 0  x10 = 1828254910 = 0x6CF8F4BE
// x_min + x mod (x_max - x_min + 1)
void randomize(unsigned* v, size_t n, unsigned x0, unsigned x_min, unsigned x_max)
{
	/*
	параллельный участок:
		[b, e) = subvector(t, T, n);
		af m(A, B);
		my_m = power(m, b);
		for i in [b,e)
			x = my_m(x0)
			v[i] = r(x) // mod
			my_m *= m
	*/
}

void home_randomize(unsigned* v, size_t n, unsigned x_min, unsigned x_max, unsigned entropy) {
	unsigned a = 3; // parameter of affine transformation
	unsigned b = 7; // same
	unsigned range = x_max - x_min + 1;

	// Lambda to transformate numbers into interval [x_min, x_max]
	auto map = [range, x_min](unsigned x) -> unsigned {
		return (x % range) + x_min;
	};

	/*
		entropy (seed) parameter using to set starting x value (x0) to get random numbers
		if a = 3, b = 4 and entropy = 10 then x0 = 10
		v[0] = 10
		v[1] = a * v[0] + b = 3 * 10 + 4 = 34
		v[2] = a * v[1] + b = 3 * 34 + 4 = 106
		...
		v[n] = a * v[n-1] + b
	*/

	// call affine transform
	affine_transform(a, b, map, v, n, entropy);
}