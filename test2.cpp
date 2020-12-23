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

	el_t box1;  // receive things from pop
	el_t box2;  // receive things from pop
	el_t total;
	while (expression[i] != '\0')
	{
		try
		{
			item = expression[i];  // current char
			if (expression.size() == 1)
				throw "Not enough numbers";
			if ((item >= 48) && (item <= 57))			//push numbers onto stack
			{
				int num = int(item) - 48;
				postfixstack.push(num);
				i++;
			}
			else if ((item == '*') || (item == '+'))
			{
				if (postfixstack.isEmpty() != true)
					postfixstack.pop(box1);
				else
					throw stack::Overflow();

				if (postfixstack.isEmpty() != true)
					postfixstack.pop(box2);
				else
					throw stack::Underflow();

				if (item == '+')
					total = box1 + box2;
				postfixstack.pop(total);
				i++;
				if (item == '*')
					total = box1 * box2;
				postfixstack.pop(total);
				i++;
			}
			else
				throw "Not a vaild character";

		} // this closes try block
		  // Catch exceptions and report problems and quit the program now. 
		  // Error messages describe what is wrong with the expression.
		catch (stack::Overflow)
		{
			cout << "Too much numbers." << endl;
		}
		catch (stack::Underflow)
		{
			cout << "Not enough numbers." << endl;
		}
		catch (char const* errormsg) // for invalid item case
		{
			cout << errormsg << endl;
		}

		// go back to the loop after incrementing i
		i++;
	}// end of while

	 // After the loop successfully completes: 
	 // Pop the result and show it.
	int result;
	postfixstack.pop(result);
	cout << "The result is " << result << endl;
	// If anything is left on the stack, an incomplete expression 
	// was found so inform the user.
	if (postfixstack.isEmpty() == false)
	{
		cout << "Things still leftover" << endl;
		postfixstack.displayAll();
	}

}// end of the program
