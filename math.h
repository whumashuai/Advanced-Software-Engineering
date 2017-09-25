#pragma once
struct Fraction {
	int deno; //Denominator
	int numer; //Numerator
	char symbol;//Operator
};

class FractionCalculate {
public:
	int gcd(int a, int b) //Maximum common divisor
	{
		int temp, r;
		if (a < b) {
			temp = a;
			a = b;
			b = temp;
		}
		while (b != 0) {
			r = a % b;
			a = b;
			b = r;
		}
		return a;
	}
	Fraction FractionAdd(Fraction f1, Fraction f2)//Addition
	{
		Fraction f3;
		f3.deno = f1.deno * f2.deno;
		f3.numer = f1.numer * f2.deno + f1.deno * f2.numer;
		return Fractionsim(f3);
	}
	Fraction Fractionsub(Fraction f1, Fraction f2)//Subtraction
	{
		Fraction f3;
		f3.deno = f1.deno * f2.deno;
		f3.numer = f1.numer * f2.deno - f1.deno * f2.numer;
		return Fractionsim(f3);
	}
	Fraction Fractionmul(Fraction f1, Fraction f2)//Multiplication
	{
		Fraction f3;
		f3.deno = f1.deno * f2.deno;
		f3.numer = f1.numer * f2.numer;
		return Fractionsim(f3);
	}
	Fraction Fractiondiv(Fraction f1, Fraction f2)//Division
	{
		Fraction f3;
		f3.numer = f1.numer * f2.deno;
		f3.deno = f1.deno * f2.numer;
		return Fractionsim(f3);
	}
	Fraction Fractionsim(Fraction f1)//Fractional simplification
	{
		int temp = gcd(f1.deno, f1.numer);
		f1.deno /= temp;
		f1.numer /= temp;
		return f1;
	}
};