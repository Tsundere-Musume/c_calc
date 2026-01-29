#ifndef CALC_H
#define CALC_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TODO(msg)                                                              \
  do {                                                                         \
    fprintf(stderr, "%s:%d: TODO: %s\n", __FILE__, __LINE__, msg);             \
    exit(1);                                                                   \
  } while (0)

#define PANIC(...)                                                             \
  do {                                                                         \
    fprintf(stderr, "%s:%d: PANIC: ", __FILE__, __LINE__);                     \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\n");                                                     \
    exit(1);                                                                   \
  } while (0)

typedef struct {
  char *src;
  size_t pos;
  size_t length;
  bool invalid;
  const char *error_message;
} Calculator;

static void calc_init(Calculator *calc, char *src);

static char peek(Calculator *calc);
static char advance(Calculator *calc);
static double evaluate_number(Calculator *calc);
static void skip_whitespace(Calculator *calc);
static void expect(Calculator *calc, char c);

static double primary(Calculator *calc);
static double unary(Calculator *calc);
static double multiplicative(Calculator *calc);
static double additive(Calculator *calc);
static double evaluate(Calculator *calc);

static double parse_expression_statement(Calculator *calc);

static void invalidate_parser(Calculator *calc, const char *msg);
#endif
