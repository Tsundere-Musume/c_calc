# Calculator
A simple expression parser and calculator built to learn about recursive descent parsing.

# Grammar
This is the grammar the parser uses to currently parse the expression.
## Expression Grammar
``` 
expresion = additive
additive = multiplicative (("+" | "-") multiplicative)*
multiplicative = unary (("/" | "*") unary)*
unary = ("-" | "+") unary | primary
primary = Number | "(" expression ")"
```

## Statement Grammar
Since we are only dealing with simple expressions, there is only one type of statement which is an expression statement. An expression statement is just an expression followed by a newline character.
``` 
stmt = expression
```
# TODOS
- [ ] REPL 
- [ ] Support for variables and identifiers
- [ ] Write tests
- [ ] Parse Expression Statements


