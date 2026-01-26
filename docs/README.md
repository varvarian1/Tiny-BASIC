# Tiny BASIC Compiler

A step-bu-step Tiny BASIC compiler. Starting with lexer - educational and open for contributions!

### What has been implemented now and what is planned

- [x] Lexical Analyzer (Lexer)
- [ ] Syntax Analyzer (Parser)
    - [ ] Recursive descent parsing
    - [ ] Abstract Syntax Tree (AST) 
- [ ] Semantic Analysis
    - [ ] Label and jump validation (GOTO, GOSUB)
- [ ] Code Generation

### Example

```bash
10 LET A = 5 + 2 * (2 * 1) * (5 * 1)
20 PRINT A
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
