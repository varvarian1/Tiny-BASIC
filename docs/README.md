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

### Output

```bash
Token: Number      	    -> '10' (value: 0)
Token: Keyword     	    -> 'LET'
Token: Identifier  	    -> 'A'
Token: Equal       	    -> '='
Token: Number      	    -> '5' (value: 0)
Token: Plus        	    -> '+'
Token: Number      	    -> '2' (value: 0)
Token: Mult        	    -> '*'
Token: LeftParenthesis	-> '('
Token: Number      	    -> '2' (value: 0)
Token: Mult        	    -> '*'
Token: Number      	    -> '1' (value: 0)
Token: RightParenthesis	-> ')'
Token: Mult        	    -> '*'
Token: LeftParenthesis	-> '('
Token: Number      	    -> '5' (value: 0)
Token: Mult        	    -> '*'
Token: Number      	    -> '1' (value: 0)
Token: RightParenthesis	-> ')'
Token: Number      	    -> '20' (value: 0)
Token: Keyword     	    -> 'PRINT'
Token: Identifier  	    -> 'A'
```

### Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```
