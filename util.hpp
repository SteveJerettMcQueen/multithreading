/*



*/

#ifndef _Util_H
#define _Util_H

#include <regex>
#include <string>
#include <vector>

// Return indices for specified splits
std::vector<int> split_indices(std::regex &rex, std::regex &rex2, 
    int max_splits, std::string &input);

#endif
