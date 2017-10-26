/*


*/

#ifndef _Sectionize_H
#define _Sectionize_H 

#include <string>
#include <vector>
#include <pthread.h>


// Store input into vector
std::vector<std::vector<std::string> > vectorize(std::string &input);

// Returns true if input is valid
bool has_valid_asterisks(std::string &input);

// Function pointer
void *sectionize_runnable(void *arg);

#endif