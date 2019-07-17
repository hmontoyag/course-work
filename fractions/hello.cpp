#include <iostream>
#include<limits>

using namespace std;

int takeInteger(){
	int num;
	std::cin >> num;
		while(1){
			if(std::cin.fail()){
				printf("Wrong input. Please type a valid integer.\n\n");
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				std::cin >> num;
			}
			if(!std::cin.fail()){
				break;
			}

		}
		return num;

}


int main(){

	int call = -1;
	int exit = 0;
	
	while(!exit){
		printf("Select an operation (type num)\n");
		printf("1: Add\n");
		printf("2: Substract\n");
		printf("3: Multiply\n");
		printf("4: Divide\n");
		printf("5: Compare\n");
		printf("6: Power\n");
		printf("7: Decimal -> Fraction\n");
		printf("8: Fraction -> Decimal\n");
		printf("0: Exit\n\n");
		
		call = takeInteger();
		while(1){
			if(call < 0 || call > 8){
				printf("Please type an integer for a valid function.\n\n");
				call = takeInteger();
			} else {
				break;
			}
		}
		/*while(1){
			if(std::cin.fail() || call < 0 || call > 8){
				printf("Wrong input. Please type a valid integer.\n");
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				std::cin >> call;
			}
			if(!std::cin.fail()){
				break;
			}

		}*/
		
		if(call == 0){
				printf(" - Bye - \n");
				exit = 1;

		} else if (call == 1){		/* add */



		} else if (call == 2){ 		/* substract */
		

				
		} else if (call == 3){ 		/* multiply */
		

				
		} else if (call == 4){ 		/* divide */
		

				
		} else if (call == 5){ 		/*	compare */
		

				
		} else if (call == 6){ 		/* 	power */
		

				
		} else if (call == 7){ 		/* decimal -> fraction */
		

				
		} else if (call == 8){ 		/* fraction -> decimal */
		

				
		} 
		
	
	
	
	}
	return 0;
}
