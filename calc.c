#include "calc.h"

#define MAX_INPUT 1024

void run_repl() {
  char input[MAX_INPUT];
  printf("You know how to quit a REPL, it's not vim.\n");

  Calculator calc = {};
  while (true) {
    printf("> ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
      break;
    }

    size_t length = strcspn(input, "\n");
    if (length != 0) {
      calc_init(&calc, input);
      double result = evaluate(&calc);
      if (calc.invalid) {
        printf("%s\n", calc.error_message);
      } else {
        printf("= %f\n", result);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    run_repl();
  } else {
    Calculator calc = {};
    for (int i = 1; i < argc; ++i) {
      calc_init(&calc, argv[i]);
      double result = evaluate(&calc);
      printf("%f\n", result);
    }
  }
  return 0;
}

// Parsing specific functions
static double evaluate(Calculator *calc) { 
	return parse_expression_statement(calc);
}

// TODO: check for whitespace edge cases
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
// Otherwise, invalidates the parser
static void expect(Calculator *calc, char c) {
  if (peek(calc) != c) {
    // sprintf(calc->error_message, "Expected %c, got %c", c, peek(calc));
    invalidate_parser(calc, "Didn't get the expected token");
  }
  advance(calc);
}

// Initializes a Calculator struct with a string
static void calc_init(Calculator *calc, char *src) {
  calc->pos = 0;
  calc->src = src;
  calc->length = strlen(src);
  calc->invalid = false;
  calc->error_message = NULL;
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
    invalidate_parser(calc, "Expected a number.");
  }

  calc->pos += (end - start);
  return result;
}

static void invalidate_parser(Calculator *calc, const char *msg) {
  calc->invalid = true;
  calc->error_message = msg;
}

static double parse_expression_statement(Calculator *calc) {
	double result = additive(calc);

	char c = peek(calc);
	if (c != '\n' && c != '\0') {
		invalidate_parser(calc, "invalid expression");
		return 0;
	}
	return result;
}

