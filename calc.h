#ifndef CALC_H
#define CALC_H

#include <stdlib.h>
#include <string.h>

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
#endif
