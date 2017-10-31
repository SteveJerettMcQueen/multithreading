/*


*/

#ifndef _Hill_H
#define _Hill_H 

#include <regex>
#include <string>
#include <vector>

// Valid Expression for hill decipher
bool valid_hill_expr(std::string &input);

// Hill algorithm for deciphering input
std::string do_hill_decipher(std::string &input);

// Function Pointer
void* hill_runner(void *arg);

#endif 