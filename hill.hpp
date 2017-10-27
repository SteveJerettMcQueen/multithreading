/*


*/

#ifndef _Hill_H
#define _Hill_H 

#include <regex>
#include <string>
#include <vector>

// Store input into a vector
std::vector<std::vector<std::string> > vectorize_hill(std::string &input);

// Valid Expression for hill decipher
bool is_valid_hill_expr(std::string &input);

// Vaild inputs for hill decipher
bool are_valid_input_parts(std::regex &rex, std::regex &rex2, 
    std::string &input_part_1, std::string &input_part_2);

// Function Pointer
void* hill_runnable(void *arg);

#endif 