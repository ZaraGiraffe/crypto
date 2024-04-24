#ifndef CRYPTOLABS_PRIME_TESTS_H
#define CRYPTOLABS_PRIME_TESTS_H

#include "zint.h"



bool miller_rabin(const uzint &n, int k) {
	uzint two(2);
	uzint one(1);
	if (n == two)
		return true;
	if (n.get(0) % (u64)2 == (u64)0 || n == one)
		return false;
	uzint d = n - one;
	int s = 0;
	

	while (d.get(0) % (u64)2 == (u64)0) {
		d = d / two;
		s++;
	}

	RandomUzintGenerator gen(two, n - two);
	for (int i = 0; i < k; i++) {
		uzint a = gen.generate();
		uzint x = a.pow(d, n);
		uzint y;
		for (int j = 0; j < s; j++) {
			y = (x * x) % n;
			if (y == one && x != one && x != n - one)
				return false;
			x = y.copy();
		}
		if (y != one)
			return false;
	}

	return true;
}


#endif CRYPTOLABS_PRIME_TESTS_H
