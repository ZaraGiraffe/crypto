#include "zint.h"
#include "prime_tests.h"
#include <iostream>

using namespace std;

int main() {
	uzint mini = get_from_base10("347865923683765385967453");
	uzint maxi = get_from_base10("375387756378573256373853");
	RandomUzintGenerator generator(mini, maxi);
	uzint num = generator.generate();
	cout << get_base10(num) << endl;

	for (int i = 1; i < 30; i++) {
		uzint p(i);
		cout << get_base10(p) << " is prime? " << miller_rabin(p, 100) << endl;;
	}

	uzint two_pow_256 = get_from_base10("115792089237316195423570985008687907853269984665640564039457584007913129639936");
	uzint bigprime = uzint(2).pow(uzint(255), two_pow_256) - uzint(19);
	cout << get_base10(bigprime) << " is prime? " << miller_rabin(bigprime, 20) << endl;
	uzint notprime = bigprime - uzint(10);
	cout << get_base10(notprime) << " is prime? " << miller_rabin(notprime, 20) << endl;
}