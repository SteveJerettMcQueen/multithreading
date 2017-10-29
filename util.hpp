/*



*/

#ifndef _Util_H
#define _Util_H

#include <regex>
#include <string>
#include <vector>

// Return indices for specified splits
std::vector<int> split_indices(std::regex &rex, std::regex &rex2, int max_splits, std::string &input);

// Matrix multiplication
std::vector<std::vector<int> > multiply_matrices(std::vector<int> a, std::vector<int> b);

// Reads input and returns message
std::string read_input(std::string &input, std::string &input2, int char_reads);

// Return true if input follows a certain divisibility
bool valid_input_parts(std::string &p1, std::string &p2, int char_reads);

#endif
