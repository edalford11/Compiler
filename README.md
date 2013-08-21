Compiler
========

A compiler that will read an input program and represents it in an internal data structure. The data structure should contain instructions to be executed as well as a part that represents the memory of the program (space for variables). Then the compiler will execute the data structure. This means that the program will traverse the data structure and at every node it visits, it will execute the node by changing appropriate memory locations and deciding what is the next instruction to execute (program counter). The output of the compiler is the output that the input program should produce.
The grammar for the compiler is given below:
<br>program -> var section body
id list -> ID COMMA id list
 | ID
<br>var section -> VAR var decl
<br>var decl -> id list SEMICOLON
<br>body -> LBRACE stmt list RBRACE
<br>stmt list -> stmt stmt list
 | stmt
<br>stmt -> ID = expr SEMICOLON
 | while stmt
 | if stmt
 | print stmt
<br>expr -> primary op primary
<br>primary -> ID
 | NUM
<br>op -> PLUS | MINUS | MULT | DIV
<br>print stmt -> print ID SEMICOLON
<br>while stmt -> WHILE condition body
<br>if stmt -> IF condition body
<br>condition -> primary relop primary
<br>relop -> GREATER | LESS | NOTEQUAL
