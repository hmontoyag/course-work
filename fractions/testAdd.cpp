#include <iostream>
#include <limits>
#include <regex>
#include "Fraction.hpp"

void test1(void){
	/*************
	* t1: simple correctnes
	**************/
	std::cout << "t1: simple correctnes" << std::endl;
	Fraction a = Fraction(1,2);
	Fraction b = Fraction(3,2);
	a+b;
	std::string r = a.getFraction();
	//a->printFraction();
	if(r.compare("2/1") == 0){
		std::cout << "t1 ok" << std::endl;
	} else {
		std::cout<<"error"<<std::endl;
	}

	std::cout<<"======================================"<<std::endl;
}
	/*************
	* t2: correctnes with negatives
	**************/
void test2(void){
	std::cout << "t2: correctnes with negatives" << std::endl;
	/**/
	Fraction a;
	Fraction b = Fraction(-1,2);
	Fraction c = Fraction(b);
	a.assign("3/-2");
	b.assign("-1/2");
	/**/
	a+c;
	std::string r = a.getFraction();
	//a->printFraction();
	if(r.compare("-2/1") == 0){
		std::cout << "t2 ok" << std::endl;
	} else {
		std::cout<<"error"<<std::endl;
	}
	std::cout<<"======================================"<<std::endl;
}
	/*************
	* t3: add number into failed init of fraction(defaulted to 0/1)
	* this one is forced. in running main, it would keep asking for fractions until they are
	* not too large/small to create
	**************/
void test3(void){
	Fraction a;
	Fraction b;
	std::cout << "t3: (forced) bad first fraction" << std::endl;
	/**/
	a.assign("9999999900000000000000000000000000000000000000000000/118799999");
	b.assign("1/2");
	/**/
	a+b;
	std::string r = a.getFraction();

	if(r.compare("1/2") == 0){
		std::cout << "t3ok" << std::endl;
	} else {
		std::cout<<"error"<<std::endl;
	}
	std::cout<<"======================================"<<std::endl;
}
	/*************
	* t4: add two numbers that overflow in the oeration a/b + c/d = (ad+bd)/bd
	**************/
void test4(void){
	std::cout<<"t4:  overflow in operation"<<std::endl;
	/**/
	Fraction a;
	Fraction b;
	a.assign("9999999999/9876543219");
	b.assign("9999999999/9876543219");	
	/**/
	if(a+b){
		std::cout<<"error"<<std::endl;
	} else {
		std::cout << "t4 ok" << std::endl;
	}

	std::cout<<"======================================"<<std::endl;
}
	/*************
	* t5: forced bad input (not numerical)
	**************/
void test5(void){

	std::cout<<"t5: force bad input (non numerical)"<<std::endl;
	Fraction a;
	Fraction b;
	a.assign("hello");
	b.assign("world");
	
	a+b;
	std::string r = a.getFraction();
	//a->printFraction();
	if(r.compare("0/1") == 0){
		std::cout << "t5 ok" << std::endl;
	} else {
		std::cout<<"error"<<std::endl;
	}
	std::cout<<"======================================"<<std::endl;
}

int main(){		
	std::cout << "================= TESTS FOR ADDITION =====================" << std::endl;
	test1();
	test2();
	test3();
	test4();
	test5();
}
