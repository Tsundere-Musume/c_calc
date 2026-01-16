# Calculator
A simple expression parser and calculator built to learn about recursive descent parsing.

# Grammar
This is the grammar the parser uses to currently parse the expression.
``` 
expresion = additive
additive = multiplicative (("+" | "-") multiplicative)*
multiplicative = unary (("/" | "*") unary)*
unary = ("-" | "+") unary | primary
primary = Number | "(" expression ")"
```

# TODOS
- [ ] REPL
- [ ] Support for variables and identifiers
- [ ] Write tests


