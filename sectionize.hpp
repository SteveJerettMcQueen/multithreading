/*


*/

#ifndef _Sectionize_H
#define _Sectionize_H 

#include <string>
#include <vector>
#include <pthread.h>

// Store input into a vector 1 x 3
std::vector<std::vector<std::string> > section_vectorize(std::string &input);

// Valid expression for vectorizing
bool valid_asterisks_expr(std::string &input);

// Function pointer
void *sectionize_runner(void *arg);

#endif