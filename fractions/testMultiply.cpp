#include <iostream>
#include <limits>
#include <regex>
#include "Fraction.hpp"

/*************
* t1: simple correctnes
**************/
void test1(void){

		std::cout << "t1: simple correctnes" << std::endl;
		Fraction a;
		Fraction b;
		a.assign("1/2");
		b.assign("3/2");
		a*b;
		std::string r = a.getFraction();
		//a->printFraction();
		if(r.compare("3/4") == 0){
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
	
		Fraction a;
		Fraction b;
		std::cout << "t2: correctnes with negatives" << std::endl;
		/**/
		a.assign("3/-2");
		b.assign("1/2");
		/**/
		a*b;
		std::string r = a.getFraction();
		//a->printFraction();
		if(r.compare("-3/4") == 0){
			std::cout << "t2 ok" << std::endl;
		} else {
			std::cout<<"error"<<std::endl;
		}
		std::cout<<"======================================"<<std::endl;
}
		/*************
		* t3: multiply fractions with lots of digits, that should not overflow
		**************/
void test3(void){
		std::cout << "t3: correctnes with seemingly large num/den" << std::endl;
		Fraction a;
		Fraction b;
		/**/
		a.assign("22222/44444");
		b.assign("3333/66666");	
		/**/
		if(!(a*b)){
			std::cout<<"error"<<std::endl;
		} else {
			std::cout << "t3 ok" << std::endl;
		}

		std::cout<<"======================================"<<std::endl;
}

		/*************
		* t4: actual overflow
		**************/
void test4(){
		std::cout << "t4: actual overflow" << std::endl;
		Fraction a;
		Fraction b;
		/**/
		a.assign("9785/951236");
		b.assign("98358/951231");	
		/**/
		if((a*b)){
			std::cout<<"error"<<std::endl;
		} else {
			std::cout << "t4 ok" << std::endl;
		}

		std::cout<<"======================================"<<std::endl;
}
		/*************
		* t5: correctnes with 0
		**************/
void test5(){
		Fraction a;
		Fraction b;
		std::cout << "t5: correctnes with 0" << std::endl;
		/**/
		a.assign("3/-2");
		b.assign("0/2");
		/**/
		a*b;
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
	std::cout << "================= TESTS FOR MULTIPLICATION =====================" << std::endl;
	test1();
	test2();
	test3();
	test4();
	test5();
	
}
