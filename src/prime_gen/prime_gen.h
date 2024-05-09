#ifndef CRYPTOLABS_PRIME_GEN_H
#define CRYPTOLABS_PRIME_GEN_H

#include "zint.h"
#include "prime_tests.h"
#include <random>


std::mt19937_64 gen;
std::uniform_int_distribution<u64> dist(0, 1);

uzint generate_odd_number(int bit_len) {
	uzint num(1);
	for (int i = 0; i < bit_len - 2; i++) {
		num = num * uzint(2) + uzint(dist(gen));
	}
	num = num * uzint(2) + uzint(1);
	return num;
}


uzint generate_prime(int bit_len, int miller_tries, int random_tries) {
	for (int i = 0; i < random_tries; i++) {
		uzint number = generate_odd_number(bit_len);
		int is_prime = miller_rabin(number, miller_tries);
		if (is_prime)
			return number;
	}
	return uzint(1);
}


#endif // CRYPTOLABS_PRIME_GEN_H