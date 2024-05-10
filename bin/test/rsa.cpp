#include "zint.h"
#include "euclid.h"
#include "rsa.h"
#include "prime_gen.h"
#include <iostream>


using namespace std;


int main() {

	uzint p = generate_prime(10, 20, 100);
	uzint q = generate_prime(10, 20, 100);
	uzint m = RandomUzintGenerator(uzint(1), uzint(1024)).generate();

	Alice alice(p, q);
	Bob bob(m);
	
	PublicKey key = alice.get_public_key();
	uzint enc = bob.encode_message(key);
	uzint m2 = alice.decode_message(enc);

	cout << get_base10(m) << endl;
	cout << get_base10(enc) << endl;
	cout << get_base10(m2) << endl;
}