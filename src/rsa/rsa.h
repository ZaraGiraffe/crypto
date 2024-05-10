#ifndef CRYPTOLABS_RSA_H
#define CRYPTOLABS_RSA_H

#include "zint.h"
#include "euclid.h"


struct PublicKey {
	uzint n;
	uzint e;
};

struct Alice {

	Alice(const uzint &p, const uzint &q) {
		n = p * q;
		ln = lcm(p - uzint(1), q - uzint(1));
		RandomUzintGenerator gen(uzint(2), ln - uzint(1));
		e = gen.generate();
		while (gcd(e, ln) != uzint(1))
			e = gen.generate();
		d = inverse_module(e, ln);
	}

	PublicKey get_public_key() {
		return PublicKey{ n, e };
	}

	uzint decode_message(const uzint &enc) {
		return enc.pow(d, n);
	}

private:
	uzint n;
	uzint ln;
	uzint e;
	uzint d;
};


struct Bob {

	Bob(const uzint &_m) {
		m = _m;
	}

	uzint encode_message(PublicKey key) {
		return m.pow(key.e, key.n);
	}

private:
	uzint m;
};


#endif // CRYPTOLABS_RSA_H
