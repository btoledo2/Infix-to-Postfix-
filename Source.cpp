#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;


template <class T>
struct node
{
	T f1;
	node<T>*next;
};
template <class T>
class sstack
{
public:
	node<T>*top;
	sstack()
	{
		top = nullptr;
	}
	void push(T v) // will add element to the top
	{
		node<T> *temp = new node<T>;
		temp->f1 = v;
		temp->next = top; //the top will be the added element
		top = temp;
	}
	void pop(T &x) // will just delete the top element
	{
		node <T>*temp = top;
		x = temp->f1;
		top = temp->next; // the new top will be the element under the top
		delete temp;
	}
	T peek()
	{
		if (!isEmpty())
			return top->f1;
	}
	int isEmpty()
	{
		return top == nullptr;
	}
};
class check // This class all it does is checks if the equation is valid 
{
public:
	int check1(string x, ofstream &outFile)// check one checks if parathesis are balance outputs error otherwise
	{
		string temp = x;
		cout <<"should not have anyspaces:" <<x<< endl;
		system("pause");
		sstack<char> billy;
		
			for (int i = 0; i < x.length(); i++)
			{
				if (x.at(i) == '(' || x.at(i) == ')')
				{

					if (billy.isEmpty() == 1)
					{
						if (x.at(i) == ')')
						{
							outFile << "error" << endl;
							return 1;
						}
						else
							billy.push(x.at(i));
					}
					else
					{
						if (billy.peek() == x.at(i))
						{
							billy.push(x.at(i));
						}
						else if (billy.peek() != x.at(i))
						{
							char temp = billy.peek();
							billy.pop(temp);
						}
					}
				}

			}
		
			if (billy.isEmpty() == 0)
			{
				outFile << "error" << endl;
				return 1;
			}
		return 0;
	}
	int check2(string x, ofstream &outFile) // checks for other errors need to clean it up but it works for now
	{
		cout << "Should this the other bullshit" << x << endl;
		int NS = x.length() - 1;
		if (x.at(0) == '/' || x.at(0) == '*')
		{
			outFile << "error" << endl;
			return 1;
		}
		else if (x.at(NS) > 57)
		{
			outFile << "error" << endl;
			return 1;
		}
		else if (x.at(NS) < 40)
		{
			outFile << "error" << endl;
			return 1;
		}
		else if (x.at(NS) == '+' || x.at(NS) == '-' || x.at(NS) == '*' || x.at(NS) == '/')
		{
			outFile << "error" << endl;
			return 1;

		}
		else
		{
			for (int i = 0; i < x.length() - 1; i++)
			{

				if (x.at(i) == '+' || x.at(i) == '-' || x.at(i) == '*' || x.at(i) == '/')
				{
					if (x.at(i + 1) == '+' || x.at(i + 1) == '-' || x.at(i + 1) == '*' || x.at(i + 1) == '/' || x.at(i + 1) == ')')
					{
						outFile << "error" << endl;
						return 1;
					}
				}
				else if (x.at(i) == ')')
				{
					if (x.at(i + 1) == '0' || x.at(i + 1) == '1' || x.at(i + 1) == '2' || x.at(i + 1) == '3' || x.at(i + 1) == '4' || x.at(i + 1) == '5' || x.at(i + 1) == '6' || x.at(i + 1) == '7' || x.at(i + 1) == '8' || x.at(i + 1) == '9' || x.at(i + 1) == '(')
					{
						outFile << "error" << endl;
						return 1;
					}
				}
				else if (x.at(i) == '0' || x.at(i) == '1' || x.at(i) == '2' || x.at(i) == '3' || x.at(i) == '4' || x.at(i) == '5' || x.at(i) == '6' || x.at(i) == '7' || x.at(i) == '8' || x.at(i) == '9')
				{
					if (x.at(i + 1) == '(')
					{
						outFile << "error" << endl;
						return 1;
					}
				}
				else if (x.at(i) == '(')
				{
					if (x.at(i + 1) == '/' || x.at(i + 1) == '*' || x.at(i + 1) == ')')
					{
						outFile << "error" << endl;
						return 1;
					}
				}
				else if (x.at(i) != '0' || x.at(i) != '1' || x.at(i) != '2' || x.at(i) != '3' || x.at(i) != '4' || x.at(i) != '5' || x.at(i) != '6' || x.at(i) != '7' || x.at(i) != '8' || x.at(i) != '9' || x.at(i) != '(' || x.at(i) != '+' || x.at(i) != '-' || x.at(i) != '*' || x.at(i) != '/' || x.at(i) != ')' || x.at(i) != '=')
				{
					outFile << "error" << endl;
					return 1;
				}

			}
		}
		return 0;
	}
	int precedence(char ToPostFix)
	{
		if (ToPostFix == '/' || ToPostFix == '*')
		{
			return 2;
		}
		else if (ToPostFix == '-' || ToPostFix == '+')
		{
			return 1;
		}
		else
		{
			return 0;
		}

	}
	bool Operator(char x)
	{

		if (x == '+' || x == '-' || x == '*' || x == '/')
		{
			return true;
		}

		return false;

	}
	string removeSpaces(string &str) // found this in geeksforgeeks it removes spaces from a string
	{
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		return str;
	}
	string addZero(string &x) // found this online 
	{
		int t;
		if (Operator(x[0]))
		{
			x.insert(0, "0");
			t = 2;
		}
		else
		{
			t = 1;
		}
		for (int i = t; i < x.length(); i++)
		{
			if (Operator(x[i]) && x[i - 1] == '(')
			{
				x.insert(i, "0");
				i++;
			}

		}
		/*for (int i = 0; i < x.length(); i++)
		{
			cout << x.at(i);

		}*/
		return x;
	}
	string infixtopostfix(string &x)
	{
		cout << "inside infix func " << x << endl;
		string postfix = "";
		char temp;
		sstack<char> bobby; // will use this stack to hold onto operators and parentheses
		for (int i = 0; i < x.length(); i++)
		{
			if (isdigit(x.at(i)))
			{
				postfix += x.at(i); // we can do this since by default digits will always have higher precedence 
			}
			else if (x.at(i) == '(')
			{
				
				bobby.push(x.at(i));
			}
			else if (x.at(i) == ')')
			{
				
				postfix += ' ';
				while (bobby.isEmpty() == 0 && bobby.peek() != '(')
				{
					postfix += ' ';
					temp = bobby.peek();
					postfix += temp;
					bobby.pop(temp);
				}
				bobby.pop(temp);
				postfix += ' ';
				/*if (bobby.peek() == '(')
				{
					temp = bobby.peek();
					bobby.pop(temp);
				}*/
				/*if (Operator(x.at(i)) && bobby.peek() == '(')
				{
					bobby.push(x.at(i));
				}*/
			}
			/*else
			{
				postfix += ' ';
				while (bobby.isEmpty() == 0 && precedence(x.at(i)) <= precedence(bobby.peek()))
				{
					temp = bobby.peek();
					postfix += temp;
					bobby.pop(temp);

				}
				bobby.push(x.at(i));

			}*/
			else  
			{
				postfix += ' ';
				if (precedence(Operator(x.at(i))) <= precedence(bobby.peek()))
				{
					while (precedence(x.at(i)) <= precedence(bobby.peek()) && bobby.isEmpty()==0)
					{
						postfix += ' ';
						temp = bobby.peek();
						postfix += temp;
						bobby.pop(temp);
					}
					bobby.push(x.at(i));
				}
						
				else if(precedence(x.at(i)) > precedence(bobby.peek()))
				{
					bobby.push(x.at(i));

				}


			}
		}
		while (bobby.isEmpty() == 0)
		{
			postfix += ' ';
			temp = bobby.peek();
			postfix += temp;
			bobby.pop(temp);
		}

		//cout << postfix;
		postfix += ' ';
		return postfix;
	}
	long long int evauluate(string PostFix) 
	{
		sstack <long long int>steve;
		string value = "";
		for (int i = 0; i < PostFix.length(); i++) 
		{
			if (PostFix.at(i) == ' ') 
			{
				continue;
			
			}
			else if (isdigit(PostFix.at(i))) 
			{
				value = "";
				while (PostFix.at(i) != ' ')
				{
					value += PostFix.at(i);
						i++;
				}
				steve.push(stoll(value));
			
			}
			else if (Operator(PostFix.at(i))) 
			{
				long long Value1 = steve.peek();
				steve.pop(Value1);
				long long Value2 = steve.peek();
				steve.pop(Value2);
				switch (PostFix.at(i))
				{
				case '+':
					steve.push(Value2 + Value1);
					break;
				case '-':
					steve.push(Value2 - Value1);
					break;
				case '*':
					steve.push(Value2 * Value1);
					break;
				case '/':
					steve.push(Value2 / Value1);
					break;
				}
			}
		}
		long long int solution = steve.peek();
		steve.pop(solution);
		return solution;
	}

	
};

int main(int argc, char* argv[])
{
	//ArgumentManager am(argc, argv);
	//const string in = am.get("input");
	//const string out = am.get("output");

	string str, temp1;
	check bob;


	ifstream inFile("input32.txt");
	
	ofstream dataOut("output.txt");

	int count = 0;
	int t = 0;
	while (!inFile.eof())
	{
		getline(inFile, temp1);
		int test = 0;
		int test2 = 0;
		if (temp1 != "") 
		{
			count++;
			string original = temp1;
			bob.removeSpaces(temp1);
			test = bob.check1(temp1, dataOut);
			if (test == 0)
			{
				test2 = bob.check2(temp1, dataOut);
				if (test2 == 0) 
				{

					bob.addZero(temp1);
					temp1 = bob.infixtopostfix(temp1);
					cout << "postFix " << temp1;
					long long int result = bob.evauluate(temp1);
					dataOut << original << "=" << result << endl;
					system("pause");
				}
			}
		
		
		
		}
	}
	if (count == 0) 
	{
		dataOut << "error" << endl;
	}
	return 0;
}