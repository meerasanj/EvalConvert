#include <iostream>
#include <string>
#include <cstdlib>
#include <string>
#include "stack.h"
#include <sstream>

using namespace std;

// defines classes for exception cases 
class DataError{};
class DivisionByZero{};
class StackUnderflow{};

// function prototypes
string getPostfixExpression();
void evalPostfix(const string postfix, const string operators);
bool goAgain();

// main method
int main(int argc, char *argv[]) {
	const string validInput = "0123456789 _+-*/%;";
	const string operators = "+-*/%";
	do {
		try {
			string postfix = getPostfixExpression(); // calls method to read in postfix expression
			for(int i = 0; i < postfix.length(); i++) {
				char c = postfix.at(i);
				if(validInput.find(c) == string::npos && c != ' ') { // checks if each character is valid input
					throw DataError();
				}
			}
			evalPostfix(postfix, operators); // calls method to evaluate postfix
		} catch (const DataError exc) {
			cerr << "Exception -- You Have entered An Invalid Expression." << endl;
			cin.clear();
		} catch (const DivisionByZero exc) {
			cerr << "Division By Zero Exception -- Now Exiting." << endl;
		} catch (const StackUnderflow exc) {
			cerr << "Stack Underflow Exception -- Now Exiting." << endl;
			cin.clear();
		}
	} while(goAgain()); // continues while user wants to goAgain
	return 0;
}

// method to perform arithmetic operations of + _ * / % 
int performOperation(char op, int a, int b) {
	switch (op) {
		case '+': 
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if(b == 0) {
				cout << "Token = /	 Pop " << b << "       Pop " << a << endl;
				throw DivisionByZero();
			}
			return a / b;
		case '%':
			return a % b;
		default:
			throw DataError();
	}
}

// method to evaluate postfix expression
void evalPostfix(const string postfix, const string operators) {
	stack<int> opStack; // creates stack to store operands 

	for(int i = 0; i < postfix.length(); i++) { // iterate through each character in string postfix 
		char currentChar = postfix.at(i);
		int operand = 0;
		
		if(isdigit(currentChar) || (currentChar == '_')) { // if it is an operand (either a number or negative number)
		// https://cplusplus.com/reference/cctype/isdigit/ <-- source for isdigit
			int sign = 1;
			
			if(currentChar == '_') { 
				sign = -1;
				i++;
			}
			while (i < postfix.length() && isdigit(postfix.at(i))) {
				operand = operand * 10 + (postfix.at(i) - '0'); // update operand 
				i++;	
			}
			operand *= sign;
			i--;
			
			// convert int to string 
			stringstream ss;
			ss << operand;
			string operandStr = ss.str();
	
			opStack.push(operand);
			cout << "Token = " << operandStr << "        Push " << operandStr << "\n";	
		
			// handle consecutive negative integers
			char front = postfix.at(i + 2);
			if(front == '_') {
				i += 2;
				while (i < postfix.length() && isdigit(postfix.at(i))) {
                   	        	operand = operand * 10 + (postfix.at(i) - '0');                                 
                                	i++;
                        	}
                        	operand *= -1;
                        	i--;
			}	
			
			// handle intOp attachment (2+)
			if (i + 1 < postfix.length() && (operators.find(i+1) != string::npos)) { // if i + 1 is less than length AND i + 1 is an operator
												// https://www.geeksforgeeks.org/stringnpos-in-c-with-examples/ 
												// string::npos source
				while (i < postfix.length() && isdigit(postfix.at(i))) {
					operand = operand * 10 + (postfix.at(i) - '0');
					i++;
                        	}
                        	operand *= sign;
				opStack.push(operand);
				cout << "Token = " << operandStr << "        Push " << operandStr << "\n";
			} 	
		} else if(operators.find(currentChar) != string::npos) { // if it is an operator
			if(opStack.isEmpty()) {
				throw StackUnderflow();
			}	
			int op1 = opStack.topAndPop();
			if(opStack.isEmpty()) {
				throw StackUnderflow();
			}
			int op2 = opStack.topAndPop();
			int result = performOperation(currentChar, op2, op1);
			opStack.push(result);
			cout << "Token = " << currentChar << "        Pop " << op1 << "        Pop " << op2 << "        Push " << result << "\n";
			
			// handle opInt attachment 
			if (i + 2 < postfix.length() && (postfix.at(i+1) == '_'))  { //op followed by negative int (+_2)
				operand = -1 * (postfix.at(i + 2) - '0');
				opStack.push(operand);
				cout << "Token = " << operand << "      Push " << operand << endl;
				i += 2;
			} else if(i + 1 < postfix.length() && isdigit(postfix.at(i + 1))) {
					operand = postfix.at(i + 1) - '0';
					opStack.push(operand);
					cout << "Token = " << operand << "        Push " << operand << endl;
					i++;
			}
		} else if(currentChar == ';') {
			if(opStack.isEmpty()) {
				throw StackUnderflow();
			}
			operand = opStack.topAndPop();
			cout << "Token = ;        Pop " << operand << endl;
		}
	}	
}

// method to return the postfix expression entered in by the user 
string getPostfixExpression() {
	cout << "@@@@@@@@@@@@@@@@@ THE POSTFIX EVALUATOR @@@@@@@@@@@@@@@@@\n";
	cout << "Your RPN Expression : ";
	string postfix;
	getline(cin, postfix); // reads user input 
	return postfix;
}

// boolean method to ask the user if they want to enter another expression 
bool goAgain() {
	string input;
	
	while(true) {
		cout << "Go Again? (Y/N): ";
		getline(cin, input); // reads user input
		
		if (input.length() == 1 && (input[0] == 'y' || input[0] == 'Y')) {
			return true;
		} else if(input.length() == 1 && (input[0] == 'n' || input[0] == 'N')) {
			return false;
		} else {
			cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
		}
	}
}
