class Fraction {
	/*parts*/
	private:
		int numerator;		/*fractions numerator*/
		int denominator;	/*fractions denominator*/

	/*functions*/
	public:
		/* constructors */
		Fraction(void);					/* default to 0 */
		Fraction(std::string input);	/* build fraction with both fields */
		Fraction(int n, int d);
		Fraction(const Fraction &f);
		Fraction(int x);
	
		/*qol ops*/
		bool assign(std::string input);
		bool mobCheck(int a, int b);
		bool sobCheck(int a, int b);
		bool isOutOfBounds(int x);
		bool stringToFraction(std::string input);
		void signs(void);
		int findGcd(int a, int b);
		/*arithmetic ops*/
		bool operator+(Fraction b);
		bool operator-(Fraction b);
		bool operator*(Fraction b);
		bool operator/(Fraction b);
		bool operator^(int b);
		/*comp*/
		int compare(Fraction b);
		bool operator==(Fraction b);
		bool operator>(Fraction b);
		bool operator<(Fraction b);
		/*assignment*/
		void operator=(Fraction b);
		void operator+=(Fraction b);
		void operator-=(Fraction b);
		void operator*=(Fraction b);
		void operator/=(Fraction b);
		/*increment/decrement*/
		void operator++(void);
		void operator--(void);
		
		/*utility ops*/
		void reduce(void);
		void printFraction(void);
		std::string getFraction(void);
		bool buildFromDouble(double b);
		void convertToDecimal(void);
		
		

};
