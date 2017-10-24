/*


*/

#include <iostream>
#include <string>
#include <vector>

#include "fence.hpp"

void* fence_runnable(void *arg){
    
    std::vector<std::vector<std::string >> *input_vector_ptr = (std::vector<std::vector<std::string >>*) arg;
    std::vector<std::vector<std::string >> input_vector = *input_vector_ptr;

    std::cout << "Fence" << std::endl;
    return 0;
}