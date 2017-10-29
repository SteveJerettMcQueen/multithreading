/*


*/

#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "sifter.hpp"
#include "sectionize.hpp"

std::string remove_white_space(std::string &input){
    
    input.erase(
        std::remove_if(
            input.begin(), 
            input.end(), 
            std::bind(
                std::isspace<char>, 
                std::placeholders::_1, 
                std::locale::classic() 
            )
        ), 
        
        input.end()

        );
        
    return input;
    
}

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
        
        /*
            Begin Sectionize Thread
        */
        
        // Thread ID
        pthread_t sect_thread;
    
        // Thread attributes
        pthread_attr_t sect_attr;
        std::cout << ((pthread_attr_init(&sect_attr)) ?
            "Sectionize Thread Attributes Initialize Unsuccessfully" :
            "Sectionize Thread Attributes Initialize Sucessfully") << std::endl;
        
        // Create thread
        std::cout << ((pthread_create(&sect_thread, &sect_attr, sectionize_runner, &new_input)) ?
            "Sectionize Thread Created Unsuccessfully" :
            "Sectionize Thread Created Sucessfully") << std::endl;
        
        // Suspend execution, wait
        std::cout << ((pthread_join(sect_thread, NULL)) ? 
            "Sectionize Thread Joined Unsuccessfully" :
            "Sectionize Thread Joined Sucessfully") << std::endl;
            
    } else {
            
        std::cout << "Invalid Sifter Input!" << std::endl;
            
    }
    
    std::cout << ">>> Sifter Function Ended <<<" << std::endl;
}
