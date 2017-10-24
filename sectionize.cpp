/*


*/

#include <iostream>
#include <string>
#include <vector>

#include "sectionize.hpp"

void* sectionize_runnable(void *arg){
    
    std::string *new_input_ptr = (std::string*) arg;
    std::string new_input = *new_input_ptr;
    
    //Sectionize input into a 1 x 3, 2D_vector
    std::vector<std::vector<std::string> > input_vector(1, std::vector<std::string>(3,""));
    
    /*
        Add Content to vector ....
    */
    
    /*
        Begin 3 new threads:
        Fence, Hill, & Pinnacle
    
    */
    


    std::cout << ">>> Sectionize Function Ended <<<" << std::endl;
}
