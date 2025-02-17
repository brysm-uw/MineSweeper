#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include "typed_array.h"

void sort_by_magnitude(std::vector<double>&);
TypedArray<TypedArray<double>> read_matrix_csv(const string);
void write_matrix_csv(const TypedArray<TypedArray<double>>&, const string);
std::map<string, int> occurrence_map(const string);

#endif