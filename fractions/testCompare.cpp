#include <iostream>
#include <limits>
#include <regex>
#include "Fraction.hpp"

void testCompare(){
		std::cout << "================= TESTS FOR COMPARISON =====================" << std::endl;
		Fraction a;
		Fraction b;
		/*************
		* t1: greater than
		**************/
		std::cout << "t1: greater than" << std::endl;
		a.assign("21/4");
		b.assign("3/2");
		if(a.compare(b)==1){
			std::cout << "t1 ok" << std::endl;
		} else {
			std::cout<<"error"<<std::endl;
		}

		std::cout<<"======================================"<<std::endl;
		/*************
		* t2: less than
		**************/

		std::cout << "t2: less than" << std::endl;
		b.assign("21/4");
		a.assign("3/2");
		if(a.compare(b)==-1){
			std::cout << "t2 ok" << std::endl;
		} else {
			std::cout<<"error"<<std::endl;
		}

		std::cout<<"======================================"<<std::endl;
		/*************
		* t3: equal
		**************/
		std::cout << "t3: equal to" << std::endl;
		b.assign("28/4");
		a.assign("14/2");
		if(a.compare(b)==0){
			std::cout << "t3 ok" << std::endl;
		} else {
			std::cout<<"error"<<std::endl;
		}

		std::cout<<"======================================"<<std::endl;
		


}

int main(){
	testCompare();
}
