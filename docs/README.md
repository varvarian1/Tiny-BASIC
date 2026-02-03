# Tiny BASIC Interpreter

A step-bu-step Tiny BASIC interpreter. Starting with lexer - educational and open for contributions!

### What has been implemented now and what is planned

- [x] Lexical Analyzer (Lexer)
- [x] Syntax Analyzer (Parser)
    - [x] Recursive descent parsing
    - [x] Abstract Syntax Tree (AST)
- [x] Interpreter
    - [x] Expression evaluation
    - [x] Variable assignment (LET)
    - [x] Output (PRINT)
    - [ ] Conditional statements (IF-THEN)
    - [ ] Loops (FOR-NEXT)
    - [ ] User input (INPUT)

### Example

```bash
10 LET A = 5 + 2 * (2 * 1) * (5 * 1)
20 LET B = 3 * 3 + 2
30 PRINT A
40 PRINT B
```

### Lexer Output

```bash
Token: Number      	    -> '10'
Token: Keyword     	    -> 'LET'
Token: Identifier  	    -> 'A'
Token: Equal       	    -> '='
Token: Number      	    -> '5'
Token: Plus        	    -> '+'
Token: Number      	    -> '2'
Token: Mult        	    -> '*'
Token: LeftParenthesis	-> '('
Token: Number      	    -> '2'
Token: Mult        	    -> '*'
Token: Number      	    -> '1'
Token: RightParenthesis	-> ')'
Token: Mult        	    -> '*'
Token: LeftParenthesis	-> '('
Token: Number      	    -> '5'
Token: Mult        	    -> '*'
Token: Number      	    -> '1'
Token: RightParenthesis	-> ')'
Token: Number      	    -> '20'
Token: Keyword     	    -> 'PRINT'
Token: Identifier  	    -> 'A'
```

### Parser Output (AST)

```bash
LetStmt: A=
  BinaryExpr: +
    Literal: 5
    BinaryExpr: *
      BinaryExpr: *
        Literal: 2
        BinaryExpr: *
          Literal: 2
          Literal: 1
      BinaryExpr: *
        Literal: 5
        Literal: 1

PrintStmt: 
  Variable: A
```

### Program Execution

```bash
Execute: 
25
11
End of program.
```

### Quick Start

```bash
git clone https://github.com/varvarian1/Tiny-BASIC.git
cd Tiny-BASIC
mkdir build && cd build
cmake ..
cmake --build .
cd ../output
./basic ../examples/test.bas
```
