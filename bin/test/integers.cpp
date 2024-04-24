#include <iostream>
#include "zint.h"


using namespace std;


int main() {
	// all test are calculated using python

	string str_a = "547534645576436346532464222345674786578585345734";
	string str_b = "347534545745745748645848";
	uzint a = get_from_base10(str_a);
	uzint b = get_from_base10(str_b);

	uzint c = a + b;
	cout << get_base10(c) << endl;
	// 547534645576436346532464569880220532324333991582

	c = a - b;
	cout << get_base10(c) << endl;
	// 547534645576436346532463874811129040832836699886

	c = a * b;
	cout << get_base10(c) << endl;
	// 190287204330464702588560851437172918983273276228630240028446627403612432

	c = a / b;
	cout << get_base10(c) << endl;
	// 1575482645621680174253707

	c = a % b;
	cout << get_base10(c) << endl;
	// 323262287820909341187198


	string str_p = "170141183460469231731687303715884105727";
	uzint p = get_from_base10(str_p);

	c = a.pow(b, p);
	cout << get_base10(c) << endl;
	// 148936584842744867067088785429935565225

}