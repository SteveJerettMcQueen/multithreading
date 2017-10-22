/*


*/

#ifndef _Sifter_H
#define _Sifter_H 

#include <string>
#include <vector>

//Returns true if message is valid
bool isValidMessage(std::string &message);

//Returns the message into a vector
std::vector<std::vector<std::string> > sectionize(std::string &message);

//Returns the message
std::string sifter(std::string &message);

#endif