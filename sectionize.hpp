/*


*/

#ifndef _Sectionize_H
#define _Sectionize_H 

#include <string>
#include <vector>
#include <pthread.h>


// Store input into a vector
std::vector<std::vector<std::string> > vectorize_sections(std::string &input);

// Valid expression for vectorizing
bool has_valid_asterisks_expr(std::string &input);

// Function pointer
void *sectionize_runnable(void *arg);

#endif