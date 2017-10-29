/*


*/

#ifndef _Hill_H
#define _Hill_H 

#include <regex>
#include <string>
#include <vector>

// Store input into a vector 2 x 1
std::vector<std::vector<std::string> > hill_vectorize(std::string &input);

// Valid Expression for hill decipher
bool valid_hill_expr(std::string &input);

// Hill algorithm for deciphering input
void do_hill_decipher(std::string &input);

// Function Pointer
void* hill_runner(void *arg);

#endif 