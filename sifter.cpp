/*


*/

#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "sifter.hpp"
#include "sectionize.hpp"
#include "util.hpp"

bool valid_sifter_input(std::string &input){
    std::regex rex("(\\*{1,3}[A-Za-z0-9]+){1,3}"); 
	return (std::regex_match(input, rex));
}

void* sifter_runner(void *arg){
    
    std::string *input_ptr = (std::string*) arg;
    std::string input = *input_ptr;
    
    // Remove whitespaces before validation
    std::string new_input = remove_white_space(input);
    
    // Validate the input
    if(valid_sifter_input(new_input)) {
        
        struct sec_runner_struct arg_struct;
        
        arg_struct.input = new_input;
        
        // Thread ID
        pthread_t sect_thread;
    
        // Thread attributes
        pthread_attr_t sect_attr;
        pthread_attr_init(&sect_attr);
        
        // Create thread
        pthread_create(&sect_thread, &sect_attr, sectionize_runner, &arg_struct);
        
        // Suspend execution, wait
        pthread_join(sect_thread, NULL);
        
        // Return status
        std::cout << "Status: " << arg_struct.status << std::endl;
        
    } else {
            
        std::cout << "Invalid Sifter Input!" << std::endl;
            
    }
    
    std::cout << ">>> Sifter Function Ended <<<" << std::endl;
}
