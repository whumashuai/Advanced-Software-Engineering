// calgen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"math.h"
#include<iostream>
#include<stdlib.h>
#include <stdio.h>  
#include<time.h>
#include <iomanip>
#include<sstream>
#include<string>
#include<stack>
#include<deque>
using namespace std;

int num;//Count the number of correct questions
int temp;

deque<Fraction> space;
deque<Fraction> line; //Store the formula

bool isBracket(char c)//Determine whether it is brackets
{
	if (c == '(' || c == ')')
		return true;
	else
		return false;
}


int getPri(char c)//Get the priority of the symbol
{
	switch (c)
	{
	case '+':
	case '-':
		return 0;   //If it is addition and subtraction, return 0  
		break;
	case '*':
	case '/':
		return 1;   //If it is multiplied and division, returns 1 
		break;
	case '(':
	case ')':
		return -1;  //Set brackets to the lowest priority 
		break;
	default:
		break;
	}
}

void check(Fraction c, stack<Fraction>& space2, deque<Fraction>& space3)//Determine the priority of the symbol
{
	if (space2.empty())
	{
		space2.push(c);
		return;
	}

	if (isBracket(c.symbol))
	{
		if (c.symbol == '(')
			space2.push(c);
		else
		{
			while (space2.top().symbol != '(') //Pop all elements until the left parenthesis is encountered
			{
				Fraction ch = space2.top();
				space3.push_back(ch);
				space2.pop();
			}

			space2.pop();
		}
	}
	else
	{
		Fraction sym = space2.top();

		if (getPri(c.symbol) <= getPri(sym.symbol)) //Compare the priority of two symbols 
		{
			//If c's priority is smaller than or equal to the top of the stack, the stack top element is popped  
			space2.pop();
			//push it into space3 (suffix expression)  
			space3.push_back(sym);
			check(c, space2, space3);
		}
		else
		{
			//If c is greater than the top of the stack, it will push c into space2 (operator stack) 
			space2.push(c);
		}
	}
}

//Remove the element from space1 and assign the element to space2 and space3  
void allocate(deque<Fraction>& space1, stack<Fraction>& space2, deque<Fraction>& space3)
{
	while (!space1.empty())
	{
		Fraction c = space1.front();
		space1.pop_front();

		if (c.symbol == '|')
		{
			space3.push_back(c);
		}
		else
		{
			check(c, space2, space3);
		}

	}

	//If the input ends, the space2 element will pop up and join the suffix expression  
	while (!space2.empty())
	{
		Fraction c = space2.top();
		space3.push_back(c);
		space2.pop();
	}
}

//Calculate the suffix expression 
Fraction calculate(deque<Fraction> space1)
{
	stack<Fraction> space2;
	deque<Fraction> space3;
	stack<Fraction> space4;
	allocate(space1, space2, space3);
	while (!space3.empty())
	{
		Fraction c = space3.front();
		space3.pop_front();

		//If it is an operand, press it into the space4 stack  
		if (c.symbol == '|')
		{
			space4.push(c);
		}
		else     //If it is an operator, pop up the elements from the stack to calculate  
		{
			Fraction op1 = space4.top();
			space4.pop();
			Fraction op2 = space4.top();
			space4.pop();
			FractionCalculate fc;
			switch (c.symbol)
			{
			case '+':
				space4.push(fc.FractionAdd(op2, op1));
				break;
			case '-':
				space4.push(fc.Fractionsub(op2, op1));
				break;
			case '*':
				space4.push(fc.Fractionmul(op2, op1));
				break;
			case '/':
				space4.push(fc.Fractiondiv(op2, op1));
				break;
			}
		}
	}
	return space4.top();
}

void Generateoperators() //Generate the operation symbol
{
	int num = rand() % 4 + 1;
	Fraction fc;
	switch (num)
	{
	case 1:   //Addition
		fc.deno = 1;
		fc.numer = 0;
		fc.symbol = '+';
		space.push_back(fc);
		line.push_back(fc);
		break;
	case 2: //Subtraction
		fc.deno = 1;
		fc.numer = 0;
		fc.symbol = '-';
		space.push_back(fc);
		line.push_back(fc);
		break;
	case 3: //Multiplication
		fc.deno = 1;
		fc.numer = 0;
		fc.symbol = '*';
		space.push_back(fc);
		line.push_back(fc);
		break;
	case 4: //Division
		fc.deno = 1;
		fc.numer = 0;
		fc.symbol = '/';
		space.push_back(fc);
		line.push_back(fc);
		break;
	default:
		break;
	}
}

void GenerateFraction() //Generate Fraction
{
	Fraction a;
	FractionCalculate fc;
	a.numer = rand() % 10 + 1;
	a.deno = rand() % 10 + 1;
	while (a.numer >= a.deno) //To ensure that numerator are less than denominator
	{
		a.numer = rand() % 10 + 1;
		a.deno = rand() % 10 + 1;
	}
	a.symbol = '|'; //"/" means division,"|" means fraction
	a = fc.Fractionsim(a);
	space.push_back(a);
	line.push_back(a);
}

void Generateinteger() //Generate the integer
{
	int a = (rand() % 10) + 1;
	Fraction fc;
	fc.numer = a;
	fc.deno = 1;
	fc.symbol = '|';
	space.push_back(fc);
	line.push_back(fc);
}

void random() //Automatically generate integers and fractions
{
	int t = rand() % 2;
	if (t == 0)
	{
		GenerateFraction();
	}
	else
	{
		Generateinteger();
	}
}

void Answer(int k)//Output the expression and judge the correctness
{
	string n;
	string re;

	Fraction result;
	result = calculate(space);
	if (result.numer < 0 || result.deno < 0 || result.numer > 100 || result.deno > 100)//Control the final result is not negative, the numerator and denominator of the score are less than 100
	{
		temp = 1;
	}
	else
	{
		cout << k << " : ";
		while (!line.empty())  //Output the expression
		{
			Fraction fcc = line.front();
			if (fcc.symbol == '(')
			{
				cout << "(";
			}
			else if (fcc.symbol == ')')
			{
				cout << ")";
			}
			else if (fcc.symbol == '+')
			{
				cout << "+";
			}
			else if (fcc.symbol == '-')
			{
				cout << "-";
			}
			else if (fcc.symbol == '*')
			{
				cout << "×";
			}
			else if (fcc.symbol == '/')
			{
				cout << "÷";
			}
			else
			{
				if (fcc.deno == 1 && fcc.symbol == '|')
				{
					cout << fcc.numer;
				}
				else
				{
					cout << fcc.numer << "/" << fcc.deno;
				}
			}
			line.pop_front();
		}
		cout << "=";
		cin >> n;
		string tmp;
		if (result.deno == 1) //Convert the result to a string type
		{
			stringstream ss;
			ss << result.numer;
			ss >> re;
			tmp = re;
		}
		else
		{
			string a, b;
			stringstream ss;
			ss << result.numer;
			ss >> a;

			string c = "/";
			string re = a + c;
			stringstream sss;
			sss << result.deno;
			sss >> b;
			re.append(b);
			tmp = re;
		}
		if (tmp.compare(n) == 0)//The result of the string type is compared with the value entered
		{
			cout << "正确!" << endl;
			num++;
		}
		else
		{
			cout << "不正确! " << "正确答案=";
			if (result.deno == 1)
			{
				cout << result.numer;
			}
			else
			{
				cout << result.numer << "/" << result.deno << endl;
			}
		}
	}

	space.clear(); //Initialization
	line.clear();
}

void Generate(int n)
{
	for (int i = 1;i <= n;i++)
	{
		int k = i;
		srand((unsigned)time(0));
		int operatorsnum = rand() % 12 + 3;//Generate the number of operands 
		int bracketsid = rand() % 2;
		int bracketnum = 0; //The pair of brackets
		if (bracketsid == 0)//Generate left bracks
		{
			Fraction fc;
			fc.deno = 1;
			fc.numer = 0;
			fc.symbol = '(';
			space.push_back(fc);
			line.push_back(fc);
			bracketnum++;
		}

		random();

		for (int j = 0;j < operatorsnum;j++)
		{
			Generateoperators();

			bracketsid = rand() % 2;
			if (bracketsid == 0 && j<operatorsnum - 1)
			{
				Fraction fc;
				fc.deno = 1;
				fc.numer = 0;
				fc.symbol = '(';
				space.push_back(fc);
				line.push_back(fc);
				bracketnum++;
				random();
			}
			else
			{
				random();
				if (bracketnum > 0 && bracketsid == 1)
				{
					Fraction fc;
					fc.deno = 1;
					fc.numer = 0;
					fc.symbol = ')';
					space.push_back(fc);
					line.push_back(fc);
					bracketnum--;
				}
			}
		}
		while (bracketnum > 0)
		{
			Fraction fc;
			fc.deno = 1;
			fc.numer = 0;
			fc.symbol = ')';
			space.push_back(fc);
			line.push_back(fc);
			bracketnum--;
		}
		Answer(k);
		if (temp == 1)
		{
			i = i - 1;
			temp = 0;
		}
	}
}

int main(int argc, char *argv[])
{
	int n=1;
	for (int i = 0;i < argc;i++)
	{
		string str = argv[i];
		if (str == "-n")
		{
			i++;
			char *m = argv[i];
			n = *m - '0';
		}
	}
	
	int cnt = 0;
	space.clear(); //Initialization
	line.clear();
	num = 0;

	cout << "本次共" << n << "题，满分100分" << endl;
	cnt = 100 / n;
	Generate(n);//Generate the problem
	if (num == n)
	{
		cout << "本次得分 : 100.00分" << endl;
	}
	else
	{
		double score = cnt*num;
		cout.setf(ios::fixed);
		cout << "本次得分 :" << fixed << setprecision(2) << score << "分" << endl;
	}
	system("pause");
	return 0;
}

