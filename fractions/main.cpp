#include <iostream>
#include <limits>
#include <climits>
#include <regex>
#include "Fraction.hpp"

/* requests an int, and verifies that one was received */
int takeInteger(){
	int num;
	std::cin >> num;
		while(1){
			if(std::cin.fail()){
				std::cout << "Wrong input. Please type a valid integer" <<  std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> num;
			}
			if(!std::cin.fail()){
				break;
			}

		}
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return num;

}

/* requests an double, and verifies that one was received */
double takeDouble(){
	double num;
	std::cin >> num;
		while(1){
			if(std::cin.fail()){
				std::cout << "Wrong input. Please type a valid integer" <<  std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> num;
			}
			if(!std::cin.fail()){
				break;
			}

		}
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return num;
}

/* validates a string in the fraction format x/y */
bool validateFraction(std::string fraction){

	std::regex format("^-?[0-9]+/-?[0-9]+$");
	return std::regex_match(fraction, format);

}

/* requests a string in fraction format and validates it */
std::string takeFraction(){
	std::string fraction;
	std::cin >> fraction;
				while(!validateFraction(fraction)){
					std::cout << "Format the fraction as:  X/Y (with valid values)" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> fraction;
				}
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return fraction;

}

/*adds two fractions*/
void add(void){
	std::cout << "Input first fraction:" << std::endl;
	std::string first = takeFraction();
	Fraction a;
	if(!a.assign(first)){
		return;
	}
	std::cout << "Input second fraction:" << std::endl;
	std::string second = takeFraction();
	Fraction b;
	if(!b.assign(second)){

		return;
	}
	a+b;
	a.printFraction();
	return;
	
	
}

/*substraction*/
void substract(void){
	std::cout << "Input first fraction:" << std::endl;
	std::string first = takeFraction();
	Fraction a;
	if(!a.assign(first)){
		return;
	}
	std::cout << "Input second fraction:" << std::endl;
	std::string second = takeFraction();
	Fraction b;
	if(!b.assign(second)){

		return;
	}
	a-b;
	a.printFraction();
	return;

}

/*multiplication*/
void multiply(void){
std::cout << "Input first fraction:" << std::endl;
	std::string first = takeFraction();
	Fraction a;
	if(!a.assign(first)){
		return;
	}
	std::cout << "Input second fraction:" << std::endl;
	std::string second = takeFraction();
	Fraction b;
	if(!b.assign(second)){
		return;
	}
	a*b;
	a.printFraction();
	return;

}

/*division*/
void divide(void){
std::cout << "Input first fraction:" << std::endl;
	std::string first = takeFraction();
	Fraction a;
	if(!a.assign(first)){
		return;
	}
	std::cout << "Input second fraction:" << std::endl;
	std::string second = takeFraction();
	Fraction b;
	if(!b.assign(second)){
		return;
	}
	a/b;
	a.printFraction();
	return;

}

/*x to the power of*/
void power(void){
	std::cout << "Input first fraction:" << std::endl;
	std::string first = takeFraction();
	Fraction a;
	if(!a.assign(first)){
		return;
	}
	std::cout << "Input (whole) number for power:" << std::endl;
	int pow = takeInteger();

	a^pow;
	a.printFraction();
	return;

}

/*compare two fractions =, >, <*/
void compare(void){
std::cout << "Input first fraction:" << std::endl;
	//in 1
	std::string first = takeFraction();
	Fraction a;
	if(!a.assign(first)){
		return;
	}
	//in 2
	std::cout << "Input second fraction:" << std::endl;
	std::string second = takeFraction();
	Fraction b;
	if(!b.assign(second)){
		return;
	}
	//operate
	a.compare(b);

	return;

}



/*reduces a fraction as much as possible*/
void reduce(void){
std::cout << "Input fraction to reduce:" << std::endl;
	//in 1
	std::string f = takeFraction();
	Fraction a;
	//operate
	if(a.assign(f)){
		a.reduce();
		a.printFraction();
	}

	
	return;
}

void increment(void){
std::cout << "Input fraction to increase by 1:" << std::endl;
	//in 1
	std::string f = takeFraction();
	Fraction a;
	//operate
	if(a.assign(f)){
		++a;
		a.printFraction();
	}


	return;
}

void decrement(void){
std::cout << "Input fraction to decrease by 1:" << std::endl;
	//in 1
	std::string f = takeFraction();
	Fraction a;
	//operate
	if(a.assign(f)){
		--a;
		a.printFraction();
	}


	return;
}

/*decimal to fraction*/
void convertDecToF(void){
	Fraction a;
	std::cout << "Input a decimal number to convert:" << std::endl;
	double b = takeDouble();
	if(a.buildFromDouble(b)){
		a.reduce();
		a.printFraction();
	}

	return;
}

/*fraction to decimal*/
void convertFracToD(void){
	//in 1
	std::cout << "Input fraction to convert:" << std::endl;
	std::string f = takeFraction();
	Fraction a;
	//operate
	if(a.assign(f)){
		a.reduce();
		a.convertToDecimal();
	
	}

}



/* main */
int main(){

	int call = -1;
	int exit = 0;
	
	while(!exit){
		std::cout << "Select an operation (type num)" << std::endl;
		std::cout << "1: Add" << std::endl;
		std::cout << "2: Substract" << std::endl;
		std::cout << "3: Multiply" << std::endl;
		std::cout << "4: Divide" << std::endl;
		std::cout << "5: Power" << std::endl;
		std::cout << "6: Compare" << std::endl;
		std::cout << "7: Reduce" << std::endl;
		std::cout << "8: Decimal -> Fraction" << std::endl;
		std::cout << "9: Fraction -> Decimal" << std::endl;
		std::cout << "10: Increment" << std::endl;
		std::cout << "11: Decrement" << std::endl;
		std::cout << "0: Exit" << std::endl;
		
		call = takeInteger();
		/*check input is valid*/
		while(1){
			if(call < 0 || call > 11){
				std::cout << "Please type an integer for a valid function." << std::endl;
				call = takeInteger();
			} else {
				break;
			}
		}	
		if(call == 0){
				std::cout << " - Bye - " << std::endl;
				exit = 1;
		} else if (call == 1){		
			add();
		} else if (call == 2){ 
			substract();
		} else if (call == 3){ 
			multiply();	
		} else if (call == 4){ 
			divide();	
		} else if (call == 5){ 
			power();				
		} else if (call == 6){ 
			compare();		
		}  else if (call == 7){ 
			reduce();
		} else if (call == 8){ 
			convertDecToF();				
		} else if (call == 9){ 
			convertFracToD();				
		} else if (call == 10){
			increment();
		} else if (call == 11){
			decrement();
		}
	}
	return 0;
}
