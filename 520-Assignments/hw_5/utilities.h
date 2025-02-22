#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <map>
#include "typed_array.h"

void sort_by_magnitude(std::vector<double>&);
TypedArray<TypedArray<double>> read_matrix_csv(const std::string);
void write_matrix_csv(const TypedArray<TypedArray<double>>&, const std::string);
std::map<std::string, int> occurrence_map(const std::string);

#endif