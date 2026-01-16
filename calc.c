#include "calc.h"

#include <stdio.h>
#include <stdlib.h>

void run_repl() { TODO("implement REPL"); }

int main(int argc, char *argv[]) {
  if (argc < 2) {
    run_repl();
  } else {
    Calculator calc = {};
    for (int i = 1; i < argc; ++i) {
      calc_init(&calc, argv[i]);
      double result = evaluate(&calc);
      printf("%f", result);
    }
  }
  return 0;
}

// Parsing specific functions
static double evaluate(Calculator *calc) { return additive(calc); }

// TODO: check for whitespace  edge cases
static double additive(Calculator *calc) {
  double lhs = multiplicative(calc);
  skip_whitespace(calc);
  char op;
  while ((op = peek(calc)) == '+' || op == '-') {
    advance(calc);
    if (op == '+') {
      lhs = lhs + multiplicative(calc);
    } else {
      lhs = lhs - multiplicative(calc);
    }
  }
  return lhs;
}

static double multiplicative(Calculator *calc) {
  double lhs = unary(calc);
  skip_whitespace(calc);
  char op;
  while ((op = peek(calc)) == '*' || op == '/') {
    // FIXME:
    advance(calc);
    if (op == '*') {
      lhs = lhs * unary(calc);
    } else {
      lhs = lhs / unary(calc);
    }
  }
  return lhs;
}

static double unary(Calculator *calc) {
  skip_whitespace(calc);
  char op = peek(calc);
  if (op == '-' || op == '+') {
    advance(calc);
    if (op == '-') {
      return -unary(calc);
    } else {
      return unary(calc);
    }
  }
  return primary(calc);
}

static double primary(Calculator *calc) {
  skip_whitespace(calc);
  double result;
  if (peek(calc) == '(') {
    advance(calc);
    result = evaluate(calc);
    expect(calc, ')');
  } else {
    result = evaluate_number(calc);
  }
  return result;
}

// Parer helpers
static void skip_whitespace(Calculator *calc) {
  char c;
  while (calc->pos < calc->length) {
    c = peek(calc);
    if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
      break;
    }
    advance(calc);
  }
}

// Gets the character at the current position in the parser state
// Returns a null character if the parser is at then end
static char peek(Calculator *calc) {
  if (calc->pos >= calc->length)
    return 0;
  return calc->src[calc->pos];
}

// Gets the character at the current position, increments the parser state
// Returns a null character if the parser is at then end
static char advance(Calculator *calc) {
  if (calc->pos >= calc->length)
    return 0;
  return calc->src[calc->pos++];
}

// If the next character in the parser matches the argument then the parser
// state is moved forward.
// Otherwise, causes a panic
static void expect(Calculator *calc, char c) {
  if (peek(calc) != c) {
    PANIC("Expected %c, got %c", c, peek(calc));
  }
  advance(calc);
}

// Initializes a Calculator struct with a string
static void calc_init(Calculator *calc, char *src) {
  calc->pos = 0;
  calc->src = src;
  calc->length = strlen(src);
}

// Parses a string as a floating point number.
// Skips whitespaces, and stops when a non-digit or a character which is not a
// '.' is encountered.
static double evaluate_number(Calculator *calc) {
  skip_whitespace(calc);
  char *start = calc->src + calc->pos;
  char *end;
  double result = strtod(start, &end);

  if (start == end) {
    PANIC("Expected a number");
  }

  calc->pos += (end - start);
  return result;
}
