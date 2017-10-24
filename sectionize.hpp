/*


*/

#ifndef _Sectionize_H
#define _Sectionize_H 

#include <string>
#include <vector>
#include <pthread.h>

//Returns the input into a vector
std::vector<std::vector<std::string> > sectionize(std::string &input);

//Function Pointer
void* sectionize(void *arg);

#endif