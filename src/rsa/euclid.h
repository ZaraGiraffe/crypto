#ifndef CRYPTOLABS_EUCLID_H
#define CRYPTOLABS_EUCLID_H


struct EuclidResult {
	uzint x;
	uzint y;
	uzint d;
};


EuclidResult euclid(const uzint &a, const uzint &b) {
	if (a.is_zero()) {
		return EuclidResult{
			uzint(0),
			uzint(1),
			b
		};
	}
	if (b.is_zero()) {
		return EuclidResult{
			a,
			uzint(0),
			uzint(a)
		};
	}
	if (a >= b) {
		uzint q = a / b;
		uzint r = a - b * q;
		EuclidResult prev = euclid(r, b);
		prev.y = prev.y + q * prev.x;
		return prev;
	}
	else {
		uzint q = b / a;
		uzint r = b - a * q;
		EuclidResult prev = euclid(a, r);
		prev.x = prev.x + q * prev.y;
		return prev;
	}
}


uzint inverse_module(const uzint& a, const uzint& p) {
	uzint b = a % p;
	if (b.is_zero())
		return b;
	EuclidResult res = euclid(b, p);
	if (b * res.x > p * res.y)
		return res.x;
	else
		return p - res.x;
}


uzint gcd(const uzint &a, const uzint &b) {
	return euclid(a, b).d;
}

uzint lcm(const uzint& a, const uzint& b) {
	return a * b / gcd(a, b);
}


#endif CRYPTOLABS_EUCLID_H