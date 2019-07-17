#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <limits>
#include <climits>
#include <algorithm> 
#include <regex>
#include "Fraction.hpp"


/**************
default to 0/1, should not be used by operations without being assigned value
**************/
Fraction::Fraction (){
	this->numerator = 0;
	this->denominator = 1;
}

Fraction::Fraction(int n, int d){
	if(d==0){
		std::cout << "cannot have denominator=0" << std::endl;
		return;
	}
	this->numerator = n;
	this->denominator = d;
}

Fraction::Fraction(const Fraction &f){
	this->numerator = f.numerator;
	this->denominator = f.denominator;
}

Fraction::Fraction(int x){
	this->numerator = x;
	this->denominator = 1;
}

/**************
assigns values to a fraction if they are between long boundaries
**************/
bool Fraction::assign(std::string input){
	return stringToFraction(input);

}


/**************
check if number falls out of bounds; true does, false doesnt
**************/
bool Fraction::isOutOfBounds(int x){ 
	if(( x = INT_MAX && errno == ERANGE)||(x == INT_MIN && errno == ERANGE)){
		std::cout << "Number/result too small or large." << std::endl;
		errno=0;
		return true;
	}
	return false;
}

/**************
detect sum overflow/underflow= true if goes out of bounds
sum out of bounds check
**************/
bool Fraction::sobCheck(int a, int b){

	if((b > 0) && (a > INT_MAX - b)){
		std::cout << "Part of this operation would overflow." << std::endl;
		return true;
	} else if ((b < 0) && (a < INT_MAX -b)){
		std::cout << "Part of this operation would underflow." << std::endl;
		return true;
	}
	return false;
}
/**************
detect multiplication overflow/underflow= true if goes out of bounds
mult out of bounds check
**************/
bool Fraction::mobCheck(int a, int b){
	if(a==0 || b==0){
		return false;
	}
	int r = a*b;
	if(r/a!=b){
		std::cout << "Operation over/underflows." << std::endl;
		return true;
	}
	return false;
}

/**************
converts the already properly formatted string into values for numerator and denominator, if valid values it returns true for assign(), if not false
**************/
bool Fraction::stringToFraction(std::string input){
	std::regex format("^-?[0-9]+/-?[0-9]+$");
	if(!std::regex_match(input, format)){
		std::cout << "Not a valid fraction format." << std::endl;
		return false;
	}
	std::size_t index = input.find("/");
	
	int numerator = strtol(input.substr(0,index).c_str(), 0 , 10);
	if(isOutOfBounds(numerator)){
		return false;
	}
	int denominator = strtol(input.substr(index+1).c_str(), 0 , 10);
	if(isOutOfBounds(denominator)){
		return false;
	}
	
	if(denominator == 0){
		std::cout << "Division by 0 not permitted." << std::endl;
		return false;
	}
	
	this->numerator = numerator;
	this->denominator = denominator;
	signs();
	return true;

}

/**************
checks if denominator is negative, and if so, fraction * -1/-1 to shift signs to either +/+ or -/+
**************/
void Fraction::signs(void){

	if(this->denominator < 0 ){
		this->denominator *= -1;
		this->numerator *= -1;
	} 
	return;
}

int Fraction::findGcd(int a, int b){
	if(a < 0){
		a *=-1;
	}
	if(b < 0){
		b*=-1;
	}
	return b == 0 ? a : findGcd(b,a%b);
}
/**************
reduce fraction
**************/
void Fraction::reduce(){
	signs();
	if(this->numerator == this->denominator){
		this->numerator = 1;
		this->denominator = 1;
	} else {
		int n = this->numerator;
		int d = this->denominator;
		int gcd = findGcd(n, d);
		if( 1 < gcd){
			this->numerator /= gcd;
			this->denominator /= gcd;
		}
	}

	signs();
	return;
}

/**************
addition
**************/
bool Fraction::operator+(Fraction b){
	int resultNumerator;
	int resultDenominator;
	//reduce both fractions to avoid unneccesary overflow
	reduce();
	b.reduce();
	/**********
	sum is assumed in shape:
	(an/ad) + (bn/bd) = (anbd+bnbd)/resultDenominator => resultNumerator/resultDenominator;
	variables are named accordingly
	***********/
	if(mobCheck(this->numerator, b.denominator)||mobCheck(this->denominator,b.numerator)){
		return false;
	}
	int anbd = this->numerator * b.denominator;
	
	int bnad = this->denominator * b.numerator;
	if(sobCheck(anbd, bnad)){
		return false;
	}
	resultNumerator = anbd+bnad;
	if(mobCheck(this->denominator, b.denominator)){
		return false;
	}
	resultDenominator = this->denominator * b.denominator;

	this->numerator = resultNumerator;
	this->denominator = resultDenominator;
	reduce();
	//printFraction();
	return true;
		
}

/**************
substract b from current
**************/	
bool Fraction::operator-(Fraction b){
	Fraction a = Fraction(this->numerator, this->denominator);
	b.numerator *= -1;
	if(!(a+b)){
		return false;
	}
	this->numerator = a.numerator;
	this->denominator = a.denominator;
	return true;


}

/**************
multiply b into current
**************/
bool Fraction::operator*(Fraction b){
	int resultNumerator;
	int resultDenominator;
	//reduce to avoid unecc. overflow
	reduce();
	b.reduce();
	if(b.numerator == 0){
		this->numerator = 0;
		this->denominator = 1;
		reduce();
		printFraction();
		return true;
	}
	if(mobCheck(this->numerator,b.numerator)||mobCheck(this->denominator, b.denominator)){
		return false;
	}
	resultNumerator = (this->numerator * b.numerator);
	resultDenominator = this->denominator * b.denominator;
	
	this->numerator = resultNumerator;
	this->denominator = resultDenominator;
	reduce();
	//printFraction();
	return true;

}
/**************
divide current by b
**************/
bool Fraction::operator/(Fraction b){
	Fraction a = Fraction(this->numerator, this->denominator);
	if(b.numerator == 0){
		std::cout << "Cannot divide by zero." << std::endl;
		return false;
	}
	int t = b.numerator;
	b.numerator = b.denominator;  
	b.denominator = t; /*here a denomin could be 0, but only used to multiply and then its gone so should not cause trouble*/
	if(!(a*b)){
		return false;
	}
	this->numerator = a.numerator;
	this->denominator = a.denominator;
	return true;

}
/**************
current to the power of b (whole number)
**************/
bool Fraction::operator^(int b){
	//reduce current
	reduce();
	if(b == 0){
		this->numerator = 1;
		this->denominator = 1;
		printFraction();
		return true;
	}
	int n = this->numerator;
	int d = this->denominator;
	for (int i = 1; i < b; i++){
		if(mobCheck(this->numerator, n)||mobCheck(this->denominator,d)){
			return false;
		}
		n *= this->numerator;
		d *= this->denominator;
	}
	
	this->numerator = n;
	this->denominator = d;
	reduce();
	//printFraction();
	return true;


}
/**************
compares current with b, doesnt reduce, to maintain clarity of comparison
vars: a/b ? c/d ---> (ad ? cb)/bd
returns 0 if equal, 1 if greater than -1 if less= than
**************/
int Fraction::compare(Fraction b){
	
	int n1 = this->numerator;
	int d1 = this->denominator;
	int n2 = b.numerator;
	int d2 = b.denominator;
	Fraction a = Fraction(this->numerator, this->denominator);
	if(a==b){
		std::cout <<  n1 << "/" << d1 << " is equal to " << n2 << "/" << d2 << std::endl; /*"%d/%d is equal to %d/%d\n", n1, d1, n2, d2*/
		return 0;
	} else if (a>b){
		std::cout <<  n1 << "/" << d1 << " is greater than " << n2 << "/" << d2 << std::endl;
		return 1;
	} else {
		std::cout <<  n1 << "/" << d1 << " is less than " << n2 << "/" << d2 << std::endl;
		return -1;
	}

}

/**************
set of comparision operators
**************/
bool Fraction::operator==(Fraction b){
	int ad = this->numerator * b.denominator;
	int cb = this->denominator * b.numerator;
	return (ad == cb);

}
bool Fraction::operator>(Fraction b){
	int ad = this->numerator * b.denominator;
	int cb = this->denominator * b.numerator;
	return (ad > cb);
}
bool Fraction::operator<(Fraction b){
	int ad = this->numerator * b.denominator;
	int cb = this->denominator * b.numerator;
	return (ad < cb);
}

/**************
assignment ops
**************/
void Fraction::operator=(Fraction b){
	this->numerator = b.numerator;
	this->denominator = b.denominator;
}
void Fraction::operator+=(Fraction b){
	Fraction a;
	a.numerator = this->numerator;
	a.denominator = this->denominator;
	a+b;
	this->numerator = a.numerator;
	this->denominator = a.denominator;
}
void Fraction::operator-=(Fraction b){
	Fraction a;
	a.numerator = this->numerator;
	a.denominator = this->denominator;
	a-b;
	this->numerator = a.numerator;
	this->denominator = a.denominator;
}
void Fraction::operator*=(Fraction b){
	Fraction a;
	a.numerator = this->numerator;
	a.denominator = this->denominator;
	a*b;
	this->numerator = a.numerator;
	this->denominator = a.denominator;
}
void Fraction::operator/=(Fraction b){
	Fraction a;
	a.numerator = this->numerator;
	a.denominator = this->denominator;
	a/b;
	this->numerator = a.numerator;
	this->denominator = a.denominator;
}
/**************
decrement and increment ops
**************/
void Fraction::operator++(void){
	this->numerator += this->denominator;
	reduce();
	return;
}

void Fraction::operator--(void){
	this->numerator -= this->denominator;
	reduce();
	return;
}

/**************
build frm a double
**************/
bool Fraction::buildFromDouble(double b){
	if(b < -1000000 || b > 1000000){
		std::cout << "Operation goes off range." << std::endl;
		return false;
	}
	this->denominator = 1;
	int i = 0;
	while((double)(int)b != b && i < 10){
		b = b*10;
		this->denominator *= 10;
		i++;
	}
	this->numerator = (int) b;
	if(isOutOfBounds(this->numerator)){
				return false;
	}
	if (isOutOfBounds(this->denominator)){
				return false;
	}
	return true;

}

/**************
build decimal from fraction
**************/
void Fraction::convertToDecimal(void){

	std::cout << "Decimal: "  << ((double)this->numerator/(double)this->denominator)  << std::endl;
	return;
}

/*********
return str with fraction formatted, doesnt add \n
*****/
std::string Fraction::getFraction(void){
	std::string ret = std::to_string(this->numerator) + "/" + std::to_string(this->denominator);
	return ret;

}
/**************
prints
**************/
void Fraction::printFraction(void){
	if(this->denominator == 1){
		std::cout << "~~ Output: " << this->numerator << std::endl;
	} else {
		std::cout << "~~ Output: " << this->numerator << "/" << this->denominator << std::endl; /*%d/%d\n", this->numerator, this->denominator);*/
	}
	return;
}
