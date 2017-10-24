/*


*/

#ifndef _Sifter_H
#define _Sifter_H 

#include <string>
#include <vector>
#include <pthread.h>

//Remove whitespaces
std::string removeWhiteSpace(std::string &input);

//Returns true if input is valid
bool isValidInput(std::string &input);

//Returns the input
std::string sifter(std::string &input);

//Function pointer
void* sifter(void *arg);

#endif