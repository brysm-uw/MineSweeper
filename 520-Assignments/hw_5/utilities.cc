#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <regex>
#include <cctype>
#include "utilities.h"

void sort_by_magnitude(std::vector<double>& input) {
    std::sort(input.begin(), input.end(), [](const double& a,const double& b){return std::abs(a) > std::abs(b); });
}

TypedArray<TypedArray<double>> read_matrix_csv(const string path) {
    std::ifstream inputFile(path);
    TypedArray<TypedArray<double>> matrix; 
    if (!inputFile) {
        throw std::runtime_error("Unable to open file " + path);
    }
    for (string line; std::getline(inputFile, line);) {
        TypedArray<double> row;
        size_t rowIndex = 0;
        // In each line, pos will point to the place where the comma is
        // Also, since we don't have a TypedArray.push(), we need to keep track of the indexes for setting
        for (size_t pos = 0; (pos = line.find(',')) != std::string::npos; rowIndex++) {
            std::string token = line.substr(0, pos);
            // Convert token to double and push it to the row
            row.set(rowIndex, std::stod(token));
            line.erase(0, pos + 1);
        }
        // We need to add the last token to the row
        row.set(rowIndex, std::stod(line));
        matrix.set(matrix.size(), row);
    }
    inputFile.close();
    return matrix;
}

void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix, const string path) {
    std::ofstream outputFile(path);
    if (!outputFile) {
        throw std::runtime_error("Unable to open output file " + path);
    }
    for (size_t rowPtr = 0; rowPtr < matrix.size(); rowPtr++) {
        TypedArray<double> row = matrix.safe_get(rowPtr);
        for (size_t idx = 0; idx < row.size(); idx++) {
            outputFile << std::to_string(row.safe_get(idx));
            if (idx < row.size() - 1) {
                outputFile << ",";
            }
        }
        outputFile << "\n";
    }
    outputFile.close();
}

std::map<string, int> occurrence_map(const string path) {
    std::regex pattern("^[a-zA-Z0-9']+$");
    std::map<string, int> validWords;
    std::ifstream inputFile(path);
    if (!inputFile) {
        throw std::runtime_error("Unable to open input file " + path);
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        for (size_t pos = 0; (pos = line.find(' ')) != std::string::npos;) {
            std::string token = line.substr(0, pos);
            if (std::regex_match(token, pattern)) {
                std::transform(token.begin(), token.end(), token.begin(), ::tolower);
                validWords[token]++;
            }
            line.erase(0, pos + 1);
        }
    }
    if (!line.empty() && std::regex_match(line, pattern)) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        validWords[line]++;
    }
    inputFile.close();
    return validWords;
}