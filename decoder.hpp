/*


*/

#ifndef _Decoder_H
#define _Decoder_H 

#include <string>
#include <vector>
#include <pthread.h>

//Returns the message into a vector
std::vector<std::vector<std::string> > decode(std::string &input);

//Function Pointer
void* decode(void *arg);

#endif