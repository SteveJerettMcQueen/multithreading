/*


*/

#ifndef _Sifter_H
#define _Sifter_H 

#include <string>
#include <vector>
#include <pthread.h>

//Returns true if input is valid
bool isValidInput(std::string &input);

//Returns the input
std::string sifter(std::string &input);

void* sifter(void *arg);

#endif