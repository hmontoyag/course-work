#include <iostream>
#include <limits>
#include <regex>
#include "Fraction.hpp"

void substractionTests(){
std::cout << "================= TESTS FOR SUBSTRACTION =====================" << std::endl;
		Fraction a;
		Fraction b;
		/*************
		* t1: simple correctnes
		**************/
		std::cout << "t1: simple correctnes" << std::endl;
		a.assign("1/2");
		b.assign("3/2");
		a-b;
		std::string r = a.getFraction();
		//a->printFraction();
		if(r.compare("-1/1") == 0){
			std::cout << "t1 ok" << std::endl;
		} else {
			std::cout<<"error"<<std::endl;
		}

		std::cout<<"======================================"<<std::endl;
		/*************
		* t2: correctnes with negatives
		**************/
		std::cout << "t2: correctnes with negatives" <<std::endl;
		a.assign("3/-2");
		b.assign("-1/2");
		/**/
		a-b;
		r = a.getFraction();
		//a->printFraction();
		if(r.compare("-1/1") == 0){
			std::cout << "t2 ok" << std::endl;
		} else {
			std::cout<<"error"<<std::endl;
		}

		std::cout<<"======================================"<<std::endl;
		/*other cases are covered by addTests since substraction is just a->add(-b) in the end.*/
}

int main(){
	substractionTests();
}
