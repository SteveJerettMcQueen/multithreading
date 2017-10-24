/*


*/

#ifndef _Sifter_H
#define _Sifter_H 

#include <string>
#include <vector>
#include <pthread.h>

//Remove whitespaces
std::string remove_white_space(std::string &input);

//Returns true if input is valid
bool is_valid_sifter_input(std::string &input);

//Function pointer
void* sifter_runnable(void *arg);

#endif