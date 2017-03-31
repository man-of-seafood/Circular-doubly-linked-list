#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;



int main()
{
	Sequence z;
	z.insert(1);
	z.insert(3);
	z.insert(5);
	z.insert(7);
	Sequence s;
	s.insert(2);
	s.insert(4);
	s.insert(6);
	s.insert(8);
	s.insert(56);
	s.insert(6543);
	s.insert(6234234);
	Sequence p;
	interleave(z, s, p);
	p.dump();
	getchar();

}