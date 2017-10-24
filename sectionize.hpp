/*


*/

#ifndef _Sectionize_H
#define _Sectionize_H 

#include <string>
#include <vector>
#include <pthread.h>

// Returns true if input is valid
bool has_valid_asterisks(std::string &input);

// Function pointer
void *sectionize_runnable(void *arg);

#endif