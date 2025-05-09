#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stack>
#include <cstring>

using namespace std;

// given struct for tree node declaration
struct BetNode {
	char info;
	BetNode* left;
	BetNode* right;
};

// function prototypes
bool isOperand(char c);
string infixToPostfix(const string& infix);
BetNode* buildTree(const string& postfix);
void preorderTraversal(BetNode* root);

// main method
int main() {
	ifstream infile("infix.dat"); // open file input stream
	if (!infile.is_open()) { // to handle errors
		cerr << "Error opening input file." << endl;
		return 1;
	}
	string infix;
	while (getline(infile, infix)) {
		string postfixExpression = infixToPostfix(infix); // calls method to convert infix -> postfix 
		BetNode* root = buildTree(postfixExpression); // calls method to convert postfix -> BET
		preorderTraversal(root); // calls method to print prefix expression
	
		cout << endl;
	}
	infile.close(); // close input file stream
	return 0;
}

// boolean method to check if character is an operand 
bool isOperand(char c) {
	return (c >= '0' && c <= '9');
}

// method to convert an infix expression to a postfix expression
string infixToPostfix(const string& infix) {
	string postfix; // output string 
	stack<char> s; // stack creation 
	
	for (int i = 0; i < infix.length(); ++i) {
		char c = infix[i];
		if(c == ' ') {
			continue; // skip spaces 
		}
		if(isOperand(c)) {
			postfix += c; // immediately outputs operands 
			postfix += ' ';
		} else if(c == '(') {
			s.push(c);
		} else if(c == ')') {
			while (!s.empty() && s.top() != '(') { // pops all values from stack until ( is found 
				postfix += s.top();
				postfix += ' ';
				s.pop();
			}
			s.pop();
		} else { // operators 
			while (!s.empty() && s.top() != '(' && c <= s.top()) {
				postfix += s.top(); 
				postfix += ' ';
				s.pop();
			}
			s.push(c);
		}
	}
	
	while(!s.empty()) {
		postfix += s.top(); // adds remaining stack members to postfix
		postfix += ' ';
		s.pop();
	}
	
	return postfix;
}

// method to convert postfix expression to a binary expression tree
BetNode* buildTree(const string& postfix) {
	stack<BetNode*> s; // creates stack for tree construction

	for (int i = 0; i < postfix.length(); ++i) {
		char c = postfix[i];
			
		if(c == ' ') {
			continue; // skip spaces 
		}
		
		BetNode* node = new BetNode; // create new node 
		node -> info = c;// set node value 
		node -> left = node -> right = NULL; // initailize child pointers 
	
		if (isOperand(c)) { 
			s.push(node); // operands get pushed onto stack 
		} else {
			if(s.size() < 2) { // to handle errors 
				cerr << "Invalid postfix expression." << endl;
				exit(1);
			}
			node -> right = s.top();
			s.pop();
			node -> left = s.top();
			s.pop();
			s.push(node);
		}
	}
	
	if(s.size() != 1) {
		cerr << "Unable to build tree." << endl;
	}
	
	return s.top(); // returns root of tree 
}

// method to print out a preorder traversal (PLR) of tree 
void preorderTraversal(BetNode* root) {
	if(root) {
		cout << root -> info << " ";
		preorderTraversal(root -> left);
		preorderTraversal(root -> right);
	}
}

