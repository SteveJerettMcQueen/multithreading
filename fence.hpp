/*


*/

#ifndef _Fence_H
#define _Fence_H 

#include <map>
#include <regex>
#include <string>
#include <vector>

// Modifies the letter string for divisibility
std::string fence_modify_str(std::string &str, int n);

// Rearranges input matrix 
std::vector<std::vector<std::string> > rearrange(std::map<int, int> &column_map,
    std::vector<std::vector<std::string>> &input_matrix);

// Valid Expression for fence decipher
bool valid_fence_expr(std::string &input);

// Fence algorithm for deciphering input
std::string do_fence_decipher(std::string &input);

//Function Pointer
void* fence_runner(void *arg);

#endif 
