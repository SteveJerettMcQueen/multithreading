/*


*/

#include <iostream>
#include <string>
#include <vector>

#include "pinnacle.hpp"

void *pinnacle_runnable(void *arg){
    
    std::vector<std::vector<std::string >> *input_vector_ptr = (std::vector<std::vector<std::string >>*) arg;
    std::vector<std::vector<std::string >> input_vector = *input_vector_ptr;
    
    std::cout << "Pinnacle" << std::endl;
    return 0;
}