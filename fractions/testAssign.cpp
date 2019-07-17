#include <iostream>
#include <limits>
#include <regex>
#include "Fraction.hpp"

void miniTest(void){
	Fraction a = Fraction(1,2);
	Fraction b = a;
	b.printFraction(); //		1/2
	Fraction c = Fraction(b);
	c.printFraction();//		1/2
	Fraction d = Fraction(1,5);
	a = d;
	a.printFraction();//		1/5
	a = c;
	a += b;
	a.printFraction();//		1
	a += a;
	a.printFraction();//		2
	a*=2;
	a.printFraction(); //		4
	a^5;
	a.printFraction();//		1024
	b *= 8;
	a/=b;
	a.printFraction();//		256
	c = Fraction(256,2);
	a = Fraction(1,2);
	a.printFraction(); 
	b = Fraction(1,4);
	b.printFraction(); 
	c = Fraction(1,5);
	c.printFraction(); 
	a+b;
	c = a;
	c - c;
	c.printFraction(); 
}
int main(){
	miniTest();
}
