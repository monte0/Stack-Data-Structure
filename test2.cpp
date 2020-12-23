#include <iostream>
#include <stdlib.h>
#include <string>
#include "stack.h"

using namespace std;

int main()
{
	stack postfixstack;  // integer stack
	string expression;   // user entered expression

	cout << "type a postfix expression: ";
	cin >> expression;

	int i = 0;  // character position within expression
	char item;  // one char out of the expression

	el_t box1 = 0;  // receive things from pop
	el_t box2 = 0;  // receive things from pop
	el_t total = 0;
	while (expression[i] != '\0')
	{
		try
		{
			item = expression[i];  // current char
			if (expression.size() == 1)
				throw "Not enough numbers";
			else if ((item >= 48) && (item <= 57))	//push numbers onto stack
			{
				int num = int(item) - 48;
				postfixstack.push(num);
			}
			else if ((item == '*') || (item == '+'))
			{
				if(postfixstack.isEmpty() != true)	//grab the first number
					postfixstack.pop(box1);
				else
				{
					throw stack::Underflow();
				}

				if(postfixstack.isEmpty() != true)	//grab the second number
					postfixstack.pop(box2);
				else
				{
					postfixstack.push(box1);
					throw stack::Underflow();
				}

				if(item == '+')	//add both nubmers
				{
					total = box1 + box2;
					postfixstack.push(total);
				}

				if(item == '*')	//multiply both numbers
				{
					total = box1 * box2;
					postfixstack.push(total);
				}
			}
			else
				throw "Not a vaild character";

		} // this closes try block
		  // Catch exceptions and report problems and quit the program now. 
		  // Error messages describe what is wrong with the expression.
		catch (stack::Overflow)
		{
			cout << "Too much numbers." << endl;
			break;
		}
		catch (stack::Underflow)
		{
			cout << "Not enough numbers." << endl;
			break;
		}
		catch (char const* errormsg) // for invalid item case
		{
			cout << errormsg << endl;
			break;
		}

		// go back to the loop after incrementing i
		i++;
	}// end of while

	 // After the loop successfully completes: 
	if (postfixstack.isEmpty() == false)
	{
		postfixstack.pop(total);	 // Pop the result and show it.
		cout << "The result is " << total << endl;

		if (postfixstack.isEmpty() == false)// If anything is left on the stack, an incomplete expression 
		{
			cout << "Things still left on the stack" << endl;
			postfixstack.displayAll();// was found so inform the user.
		}
	}
	else
	{
		//stack is empty
	}

}// end of the program
