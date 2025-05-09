# Postfix Evaluation and Infix-to-Prefix Conversion

## Part 1: Postfix Expression Evaluator

The program `postfix.cpp` evaluates postfix expressions using a stack-based approach. The stack ensures operations are performed in the correct order according to postfix evaluation rules and tracks operands efficiently.

### Key Features

- **User Interaction**:  
  The `main` function manages user input, validates expressions, and invokes the `evalPostfix` function. A `do-while` loop enables repeated evaluations based on user input.

- **Exception Handling**:  
  Custom exception classes (`DataError`, `DivisionByZero`) handle invalid expressions and division by zero.

- **Arithmetic Operations**:  
  The `performOperation` function supports the following operators:
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`*`)
  - Division (`/`)
  - Modulus (`%`)

- **Evaluation Logic**:  
  The `evalPostfix` method:
  - Uses a stack to store operands.
  - Pushes operands and performs operations when an operator is encountered.
  - Handles edge cases such as negative integers and concatenated operands/operators.

### Compilation & Execution

```bash
c++ postfix.cpp 
./a.out
```

## Part 2: Infix-to-Prefix Expression Converter

The program `myBet.cpp` converts infix expressions to prefix form. It first converts the infix expression to postfix, constructs a Binary Expression Tree (BET) from the postfix expression, and then outputs the prefix form using preorder traversal.

### Key Features

- **Input Handling**
  - Reads infix expressions from a file named `infix.dat`.
  - Includes error handling in case the file cannot be opened.

- **Infix to Postfix Conversion**
  - The `infixToPostfix` function:
    - Appends operands directly to the output postfix expression.
    - Uses a stack to manage operators based on precedence.
    - Pushes opening parentheses to the stack.
    - On encountering a closing parenthesis, pops from the stack to the output until an opening parenthesis is found.
    - Maintains correct order of operations for complex expressions.

- **Binary Expression Tree (BET) Construction**
  - The `buildTree` function:
    - Iterates through the postfix expression.
    - Pushes operands as leaf nodes onto a stack.
    - For each operator, pops two nodes to create a new subtree and pushes the resulting node back onto the stack.

- **Prefix Expression Output**
  - After the BET is built, a **preorder traversal** is performed to generate and display the prefix expression.
  - Ensures correctness of conversion and expression hierarchy.

- **Robustness**
  - Handles edge cases such as:
    - Insufficient operands during BET construction.
    - File I/O errors when reading `infix.dat`.

### Compilation & Execution

```bash
c++ myBet.cpp 
./a.out
```

## License
 No license has been provided for this project
