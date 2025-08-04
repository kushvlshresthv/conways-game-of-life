#ifndef PATTERNS_H_
#define PATTERNS_H_
#include <stdbool.h>


void populate_with_glider(int *array, int rows, int columns, int start_row, int start_col);

void populate_array_randomly(int *array, int rows, int columns);

void populate_with_all_oscillators(int *array, int rows, int columns);

void populate_with_glider_gun(int *array, int rows, int columns);

#endif //PATTERNS_H_
