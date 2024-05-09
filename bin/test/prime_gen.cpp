#include "zint.h"
#include "prime_tests.h"
#include "prime_gen.h"
#include <iostream>

using namespace std;


int main() {
	int bit_len = 256;
	uzint some_prime = generate_prime(bit_len, 20, 3000);
	cout << get_base10(some_prime) << endl;
}