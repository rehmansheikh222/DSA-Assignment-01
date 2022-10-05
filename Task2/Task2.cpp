/*
Name:Abdul Rehman
Roll Number: BCSF20A020
*/
#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <cctype>
using namespace std;
bool matchingFamily(char a, char b)
{
	if (a == '('&&b == ')')
	{
		return true;
	}
	else if (a == '['&&b == ']')
	{
		return true;
	}
	else if (a == '{'&&b == '}')
	{
		return true;
	}
	else if (a == '<'&&b == '>')
	{
		return true;
	}
	return false;
}
bool isBalanced(string exp)
{
	stack<char> obj;
	for (int i = 0; exp[i] != '\0'; i++)
	{
		char var;
		if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[' || exp[i] == '<')
		{
			obj.push(exp[i]);
		}
		else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']' || exp[i] == '>')
		{
			if (obj.empty())
			{
				return false;
			}
			var = obj.top();
			obj.pop();
			if (!matchingFamily(var, exp[i]))
			{
				return false;
			}
		}
	}
	if (obj.empty())
	{
		return true;
	}
	return false;
}

bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
	{
		return true;
	}
	return false;
}

int precedence(char a)
{
	if (a == '+' || a == '-')
	{
		return 1;
	}
	else if (a == '*' || a == '/')
	{
		return 2;
	}
	else if (a == '^')
	{
		return 3;
	}
	return 0;
}

bool isOpeningBracket(char c)
{
	if (c == '(' || c == '{' || c == '[')
	{
		return true;
	}
	return false;
}

bool isClosingBracket(char c)
{
	if (c == ')' || c == '}' || c == ']')
	{
		return true;
	}
	return false;
}

bool isOpeningString(string c)
{
	if (c == "(" || c == "{" || c == "[")
	{
		return true;
	}
	return false;
}

string openingBracket(char c)
{
	if (c == ')')
		return "(";
	else if (c == '}')
		return "{";
	else if (c == ']')
		return "[";

}

char openingBracketChar(char c)
{
	if (c == ')')
		return '(';
	else if (c == '}')
		return '{';
	else if (c == ']')
		return '[';

}

string infixToPostfix(string exp)
{
	stack<string> obj;
	string postfix = "";
	int i = 0;
	while (i < exp.length())
	{
		if (exp[i] == ' ')
		{
			i++;
		}
		if (isOpeningBracket(exp[i]))
		{
			string temp = "";
			temp += exp[i];
			obj.push(temp);
			i++;
		}
		else if (isClosingBracket(exp[i]))
		{
			string c = openingBracket(exp[i]);
			while (obj.top() != c)
			{
				postfix+= obj.top();
				postfix += " ";
				obj.pop();
			}
			obj.pop();
			i++;
		}
		else if (isOperator(exp[i]))
		{
			if (obj.empty())
			{
				string temp = "";
				temp += exp[i];
				obj.push(temp);
				i++;
			}
			else if (isOpeningString(obj.top()))
			{
				string temp = "";
				temp += exp[i];
				obj.push(temp);
				i++;
			}
			else
			{
				string temp = obj.top();
				char c = temp[0];
				if (precedence(exp[i]) > precedence(c))
				{
					temp = "";
					temp += exp[i];
					obj.push(temp);
					i++;
				}
				else
				{
					postfix+= obj.top();
					postfix += " ";
					obj.pop();
				}
			}

		}
		else
		{
			while (i < exp.length() && !isOpeningBracket(exp[i]) && !isClosingBracket(exp[i]) && !isOperator(exp[i]))
			{
				postfix += exp[i];
				i++;
				if (exp[i] == ' ')
				{
					i++;
				}
			}
			postfix += " ";
		}
	}
	while (!obj.empty())
	{
		postfix += obj.top();
		obj.pop();
	}
	return postfix;
}

template <typename T>
T calculatedValue(char c, T first, T second)
{
	if (c == '+')
	{
		return first + second;
	}
	else if (c == '-')
	{
		return first - second;
	}
	else if (c == '*')
	{
		return first * second;
	}
	else if (c == '/')
	{
		return first / second;
	}
	else if (c == '^')
	{
		return pow(first, second);
	}
	return 0;
}

double Evaluate(string exp, bool key)
{
	if (!key)
	{
		stack<double> oprnd;
		stack<char> oprtr;
		int i = 0;
		while (i < exp.length())
		{
			if (exp[i] == ' ')
			{
				i++;
			}
			if (i < exp.length() && exp[i] >= 48 && exp[i] <= 57)
			{
				double t = 0;
				string temp = "";
				while (i < exp.length() && exp[i] != '\0' && exp[i] >= 48 && exp[i] <= 57)
				{
					temp += exp[i];
					i++;
					if (i < exp.length() && exp[i] == '.')
					{
						temp += exp[i];
						i++;
					}
				}
				t = stod(temp);
				oprnd.push(t);
			}
			else
			{
				if (i < exp.length() && (isupper(exp[i]) || islower(exp[i])))
				{
					double val;
					cout << "Enter the value of " << exp[i] << ": ";
					cin >> val;
					oprnd.push(val);
					i++;
				}
				else if (i < exp.length() && isOpeningBracket(exp[i]))
				{
					oprtr.push(exp[i]);
					i++;
				}
				else if (i < exp.length() && isClosingBracket(exp[i]))
				{
					char c = openingBracketChar(exp[i]);
					if (oprtr.empty())
					{
						cout << "The expression is invalid!" << endl;
						exit(0);
					}
					while (!oprtr.empty() && oprtr.top() != c)
					{
						char c = oprtr.top();
						oprtr.pop();
						if (oprnd.empty())
						{
							cout << "The expression is invalid!" << endl;
							exit(0);
						}
						double operand2 = oprnd.top();
						oprnd.pop();
						if (oprnd.empty())
						{
							cout << "The expression is invalid!" << endl;
							exit(0);
						}
						double operand1 = oprnd.top();
						oprnd.pop();
						oprnd.push(calculatedValue<double>(c, operand1, operand2));
					}
					i++;
					if (!oprtr.empty())
					{
						oprtr.pop();
					}
				}
				else if (i < exp.length() && isOperator(exp[i]))
				{
					if (oprtr.empty())
					{
						oprtr.push(exp[i]);
						i++;
					}
					else if (i < exp.length() && precedence(exp[i]) > precedence(oprtr.top()))
					{
						oprtr.push(exp[i]);
						i++;
					}
					else
					{
						if (oprtr.empty())
						{
							cout << "The expression is invalid!" << endl;
							exit(0);
						}
						char v = oprtr.top();
						oprtr.pop();
						if (oprnd.empty())
						{
							cout << "The expression is invalid!" << endl;
							exit(0);
						}
						double operand2 = oprnd.top();
						oprnd.pop();
						if (oprnd.empty())
						{
							cout << "The expression is invalid!" << endl;
							exit(0);
						}
						double operand1 = oprnd.top();
						oprnd.pop();
						oprnd.push(calculatedValue<double>(v, operand1, operand2));
					}
				}
			}
		}
		while (!oprtr.empty())
		{
			char v = oprtr.top();
			oprtr.pop();
			if (oprnd.empty())
			{
				cout << "The expression is invalid!" << endl;
				exit(0);
			}
			double operand2 = oprnd.top();
			oprnd.pop();
			if (oprnd.empty())
			{
				cout << "The expression is invalid!" << endl;
				exit(0);
			}
			double operand1 = oprnd.top();
			oprnd.pop();
			oprnd.push(calculatedValue<double>(v, operand1, operand2));
		}
		if (oprnd.empty())
		{
			cout << "The expression is invalid!" << endl;
			exit(0);
		}
		return oprnd.top();
	}
	else
	{
		stack<double> obj;
		int i = 0;
		while (i < exp.length())
		{
			string temp = "";
			double a;
			if (exp[i] == ' ')
			{
				i++;
			}
			if (i < exp.length() && !isOperator(exp[i]))
			{
				
				if (i < exp.length() && (isupper(exp[i]) || islower(exp[i])))
				{
					double val;
					cout << "Enter the value of " << exp[i] << ": ";
					cin >> val;
					obj.push(val);
					i++;
				}
				else
				{
					while (i < exp.length() && exp[i] != ' ' && !isOperator(exp[i]))
					{
						temp += exp[i];
						i++;
						if (i < exp.length() && exp[i] == '.')
						{
							i++;
						}
					}
					if (exp[i] == ' ')
					{
						i++;
					}
					a = stod(temp);
					obj.push(a);
				}
			}
			else
			{
				if (obj.empty())
				{
					cout << "Expression is invalid\n";
					exit(0);
				}
				double operand2 = obj.top();
				obj.pop();
				if (obj.empty())
				{
					cout << "Expression is invalid\n";
					exit(0);
				}
				double operand1 = obj.top();
				obj.pop();
				obj.push(calculatedValue<double>(exp[i], operand1, operand2));
				i++;
			}
		}
		return obj.top();
	}
}


int main()
{
	int choice;
	string exp;
	char c;
	do
	{
		cout << "Which one you want to run?" << endl;
		cout << "1. To check whether the given expression is balanced or not." << endl;
		cout << "2. To convert infix to postfix." << endl;
		cout << "3. To evaluate the expression." << endl;
		cin >> choice;
		while (!(choice > 0 && choice < 4))
		{
			cout << "Select between 1, 2 and 3: ";
			cin >> choice;
		}
		system("cls");
		if (choice == 1)
		{
			cout << "-------------------" << endl;
			cout << "Balancing checking" << endl;
			cout << "-------------------" << endl;
			cin.ignore();
			cout << "Enter the expression: ";
			cin >> exp;
			if (isBalanced(exp))
			{
				cout << "The given expression is balanced" << endl;
			}
			else
			{
				cout << "The given expression is unbalanced" << endl;
			}
		}
		else if (choice == 2)
		{
			cout << "----------------------------" << endl;
			cout << "Infix To Postfix conversion" << endl;
			cout << "----------------------------" << endl;
			cout << "Enter the Infix Expression: ";
			cin.ignore();
			getline(cin, exp);
			cout << "Postfix of " << exp << " is: " << infixToPostfix(exp) << endl;
		}
		else if (choice == 3)
		{
			int choose;
			cout << "Which expression you want to evaluate?\n";
			cout << "1. Infix.\n";
			cout << "2. Postfix.\n";
			cin >> choose;
			while (!(choose > 0 && choose < 3))
			{
				cout << "Choose between 1 and 2: ";
				cin >> choose;
			}
			if (choose == 1)
			{
				cout << "Enter the Infix Expression: ";
				cin.ignore();
				getline(cin, exp);
				cout << "Evaluated answer: " << Evaluate(exp, 0) << endl;
			}
			else if (choose == 2)
			{
				cout << "-------------" << endl;
				cout << "Instructions" << endl;
				cout << "-------------" << endl;
				cout << "--> Operands must be space separated!\n";
				cout << "--> Expressions like 5 6+ are valid\n--> Whereas expression 56+ is not valid as it is ambiguous that the number is single digit or a double digit." << endl;
				cout << "\nEnter the Postfix Expression: ";
				
				cin.ignore();
				getline(cin, exp);
				cout << "Evaluated answer: " << Evaluate(exp, 1) << endl;
			}
		}
		cout << "Do you want to run it again?(Y/N): ";
		cin >> c;
		while (!(c == 'y' || c == 'Y' || c == 'N' || c == 'n'))
		{
			cout << "Please choose between Y/N: ";
			cin >> c;
		}
		system("cls");

	} while (c == 'Y' || c == 'y');
	
	return 0;
}
