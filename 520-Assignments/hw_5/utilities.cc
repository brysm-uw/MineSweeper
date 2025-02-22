#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <regex>
#include <cctype>
#include <map>
#include <sstream>
#include "utilities.h"

void sort_by_magnitude(std::vector<double>& input) {
    // Sort the magnitude of numbers in ascending order
    std::sort(input.begin(), input.end(), [](double& a,double& b){
        return std::abs(a) < std::abs(b);
     });

     // Convert all values to abs(value)
     for(double& val : input) {
        val = std::abs(val);
     }
}

TypedArray<TypedArray<double>> read_matrix_csv(const std::string path) {
    std::ifstream inputFile(path);
    TypedArray<TypedArray<double>> matrix; 
    if (!inputFile) {
        throw std::runtime_error("Unable to open file " + path);
    }
    for (std::string line; std::getline(inputFile, line);) {
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

void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix, const std::string path) {
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

std::map<std::string, int> occurrence_map(const std::string path) {
    // Valid word definition
    std::regex pattern("^[a-zA-Z0-9']+$");
    std::map<std::string, int> validWords;
    std::ifstream inputFile(path);
    if (!inputFile) {
        throw std::runtime_error("Unable to open input file " + path);
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream instream(line);
        std::string token;
        // Use stringstream to split each line into words by white space
        while (instream >> token) {
            // Look for punctuation before the word starts that won't be considered and trim them off
            while (!token.empty() && std::ispunct(static_cast<unsigned char>(token.front())) && static_cast<unsigned char>(token.front()) != '\'') {
                token.erase(token.begin());
            }
            // Look for punctuation after the word ends that won't be considered and trim them off
            while (!token.empty() && std::ispunct(static_cast<unsigned char>(token.back())) && static_cast<unsigned char>(token.back()) != '\'') {
                token.pop_back();
            }
            // Look at the word and compare it to the valid word pattern (then transform it to lower case)
            if (std::regex_match(token, pattern)) {
                std::transform(token.begin(), token.end(), token.begin(), ::tolower);
                validWords[token]++;
            }
        }
    }
    inputFile.close();
    return validWords;
}