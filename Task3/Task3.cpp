/*
Name:Abdul Rehman
Roll Number: BCSF20A020
*/
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;
struct Atom
{
	string name;
	int count;
};
string countNoOfAtoms(string cFormula)
{
	vector<Atom> countedFormula;
	vector<Atom> temp;
	stack<Atom> atoms;
	int i = 0;
	while (i < cFormula.length())
	{
		if (i < cFormula.length() && cFormula[i] == '1')
		{
			cout << "The given formula is wrong\n";
			exit(0);
		}
		if (i < cFormula.length() && cFormula[i] == '(')
		{
			Atom t{ "(", 1 };
			atoms.push(t);
			i++;
		}
		else if (i < cFormula.length() && cFormula[i] == ')')
		{
			if (atoms.empty())
			{
				cout << "The given formula is wrong\n";
				exit(0);
			}
			while (atoms.top().name != "(")
			{
				if (atoms.empty())
				{
					cout << "The given formula is wrong\n";
					exit(0);
				}
				temp.push_back(atoms.top());
				atoms.pop();
			}
			atoms.pop();
			i++;
			int cunt = 0;
			while (i < cFormula.length() && cFormula[i] >= 48 && cFormula[i] <= 57)
			{
				cunt = cunt * 10 + (cFormula[i] - 48);
				i++;
			}
			if (cunt == 1)
			{
				cout << "The given formula is wrong\n";
				exit(0);
			}
			if (cunt == 0)
			{
				cunt = 1;
			}
			for (int j = 0; j < temp.size(); j++)
			{
				temp[j].count *= cunt;
			}
			if (!atoms.empty())
			{
				while (!temp.empty())
				{
					atoms.push(temp[0]);
					temp.erase(temp.begin());
				}
			}
			else
			{
				while (!temp.empty())
				{
					countedFormula.push_back(temp[0]);
					temp.erase(temp.begin());
				}
			}
		}
		else if (i < cFormula.length() && cFormula[i] >= 65 && cFormula[i] <= 90)
		{
			string nm = "";
			nm += cFormula[i];
			i++;
			while (i < cFormula.length() && cFormula[i] >= 97 && cFormula[i] <= 122)
			{
				nm += cFormula[i];
				i++;
			}
			int cunt = 0;
			while (i < cFormula.length() && cFormula[i] >= 48 && cFormula[i] <= 57)
			{
				cunt = cunt * 10 + (cFormula[i] - 48);
				i++;
			}
			if (cunt == 1)
			{
				cout << "The given formula is wrong\n";
				exit(0);
			}
			if (cunt == 0)
			{
				cunt = 1;
			}
			if (atoms.empty())
			{
				Atom t{ nm, cunt };
				countedFormula.push_back(t);
			}
			else
			{
				Atom t{ nm, cunt };
				atoms.push(t);
			}
		}
		else if (i < cFormula.length() && cFormula[i] >= 97 && cFormula[i] <= 122)
		{
			cout << "The given formula is wrong\n" << endl;
			exit(0);
		}
	}
	//Combining the duplicates
	for (int i = 0; i<countedFormula.size(); i++)
	{
		for (int j = i + 1; j < countedFormula.size(); j++)
		{
			if (countedFormula[i].name == countedFormula[j].name)
			{
				countedFormula[i].count += countedFormula[j].count;
				countedFormula.erase(countedFormula.begin() + j);
				j--;
			}
		}
	}
	//Sorting Elements
	for (int i = 0; i<countedFormula.size(); i++)
	{
		int min = i;
		for (int j = i + 1; j < countedFormula.size(); j++)
		{
			if (countedFormula[min].name > countedFormula[j].name)
			{
				min = j;
			}
		}
		Atom temp = countedFormula[min];
		countedFormula[min] = countedFormula[i];
		countedFormula[i] = temp;
	}
	string result = "";
	//Making final string
	while (!countedFormula.empty())
	{
		result += countedFormula[0].name;
		if (countedFormula[0].count > 1)
		{
			result += to_string(countedFormula[0].count);
		}
		countedFormula.erase(countedFormula.begin());
	}
	return result;
}
int main()
{
	string str;
	cout << "---------------" << endl;
	cout << "Instructions:\n";
	cout << "---------------" << endl;
	cout << "--> Input the formula without spaces.\n";
	cout << "--> Formulas like H2SO4 are allowed.\n";
	cout << "--> Whereas formula H1SO4 is impossible.\n";
	cout << "--> Parenthesis () are allowed in the formula\n";
	cout << "\nEnter the Chemical Formula: ";
	cin >> str;
	cout << "The count of atoms in " << str << ": " << countNoOfAtoms(str) << endl;
	return 0;
}
