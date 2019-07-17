#include <iostream>
#include <limits>
#include <regex>
#include "Fraction.hpp"


void testDivision(){
		/*division is handled as: a->divide(b/c) = a->multiply(c/b), so some cases are covered already by testMultply/test3*/
		std::cout << "================= TESTS FOR DIVISION =====================" << std::endl;
		Fraction a;
		Fraction b;
		/*************
		* t1: divide 0 by valid number
		**************/
		std::cout <<"t1: divide 0" << std::endl;
		a.assign("0/2");
		b.assign("3/2");
		a/b;
		std::string r = a.getFraction();
		//a->printFraction();
		if(r.compare("0/1") == 0){
			std::cout << "t1 ok" << std::endl;
		} else {
			std::cout<<"error"<<std::endl;
		}

		std::cout<<"======================================"<<std::endl;
		/*************
		* t2: divide BY 0
		**************/
		std::cout <<"t2: dividing by 0" << std::endl;
		/**/
		a.assign("3/-2");
		b.assign("0/2");

		if(!(a/b)){
			std::cout << "t2 ok" << std::endl;
		} else {
			std::cout<<"error"<<std::endl;
		}

		std::cout<<"======================================"<<std::endl;
		/*************/
}

int main(){
	testDivision();

}
