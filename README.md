# Welcome to My Bc
***

## Task
my_bc is a project that creates a program that allows users to calculate simple mathematical operations.

my_bc works by implementing the shunting-yard algorithm also called reverse-polish notation which is stack-based. The Shunting yard algorithm is a method for parsing arithmetical or logical expressions, or a combination of both, in infix notation, it produces a postfix notation string, also known as Reverse Polish notation (RPN). <br>

An infix expression is a form of mathematical notation most people are used to, for instance "3 + 4"; the algorithm converts this expression to a postfix notation resulting in "3 4 +". This process allows to parse infix expressions and produce postfix expressions.<br>

Our task is to to implement a lexical analysis system and implement the shunting yard algorithm to parse the expressions inputed by the user to finally output the result of the calculation of the expressions<br>

## Description
**lexical analysis:** This stage deals with first tokenizing the input string into meaningful units called 'lexemes' that are then classified according to its supposed meaning and checked for errors. <br>
    1. *Tokenization* **(lexer_system1.c)**: convert text input string into tokens, rejecting unknown characters. <br>
    2. *Token classification* **(lexer_system2.c)**: classify based on content and structure what each token is, which are essential for validation and later evaluation. <br>
    3. *Token validation* **(error_management.c)**: with lexemes classified, perform further analysis that every syntax possibilty is correct so that most predesigned errors are caught. <br>

**mathematical evaluation:** This stage deals with manipulating the tokens to generate output: first rearranging, then evaluating. <br>
    4. *Parsing infix* **(math_parsing.c)**: simplify the order of operations by rearranging the tokens into reverse-polish notation (i.e. postfix). <br>
    5. *Calculating postfix* **(math_postfix_calc.c)**: use the postfix formula as a straightforward instruction on how to evaluate the given values. <br>

## Installation
Only a gcc compiler is required. <br/>
There is no other installation needed.

## Usage
```
Usage: 
$> ./my_bc [OPERATION]

Evaluate the given values with operators in the         
intended order of operations until only one remains.    

  INPUTTING VALUE: 
      [SIGN]...[INTEGER]
          INTEGER             insert whole numbers
      +   POSITIVE SIGN       apply postive sign
      -   NEGATIVE SIGN       apply negative sign

  THROUGHPUTTING VALUE:
    [INPUT/THROUGHPUT][OPERATOR][INPUT/THROUGHPUT]
          INPUT               the given value by the user
          THROUGHPUT          the output value of a previous operation

    low precedence:
      +   ADD                 output the sum of leftside and rightside value
      -   SUBTRACT            output the difference between leftside and rightside value

    high precedence:
      *   MULTIPLY            output the product of leftside times rightside value 
      /   DIVIDE              output the quotient of leftside divided by rightside value
      %   MODULO              output the remainder of leftside divided by rightside value

  CLARIFYING PRECEDENCE:
    [SIGN]...[OPEN][OPERATION][CLOSE]
      (   OPEN      marks the beginning of parenthesis, must later be closed.    
      )   CLOSE     marks the end of parenthesis, must earlier be opened.
  
RETURN VALUE:
    0   SUCCESS
    1   FAILURE
```

### The Core Team
Programmer & Developer: Adrian Sardinata & Soraia Lima Cid

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
