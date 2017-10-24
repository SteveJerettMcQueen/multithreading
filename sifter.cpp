/*


*/

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "sifter.hpp"
#include "sectionize.hpp"


std::string removeWhiteSpace(std::string &input){
    
    
}

bool isValidInput(std::string &input){
    
	std::string regex_str = "(\\*{1,3}[A-Za-z0-9]+){1,3}";
	std::regex rex(regex_str); 
	
	return (std::regex_match(input, rex));

}

void* sifter(void *arg){
    
    std::string *input_ptr = (std::string*) arg;
    std::string input = *input_ptr;
    
    // //Tokenize the input by removing whitespaces
    std::string tokInput = input;
    
    // //Validate the input
    if(isValidInput(tokInput)) {
        
        /*
            Begin Sectionize Thread
        */
        
        //Thread ID
        pthread_t sectionizeThread;
    
        // Thread attributes
        pthread_attr_t sect_attr;
        std::cout << ((pthread_attr_init(&sect_attr)) ?
            "Sectionize Thread Attributes Initialize Unsuccessfully" :
            "Sectionize Thread Attributes Initialize Sucessfully") << std::endl;
        
        // Create thread
        std::cout << ((pthread_create(&sectionizeThread, &sect_attr, sectionize, &tokInput)) ?
            "Sectionize Thread Created Unsuccessfully" :
            "Sectionize Thread Created Sucessfully") << std::endl;
        
        //Suspend execution, wait
        std::cout << ((pthread_join(sectionizeThread, NULL)) ? 
            "Sectionize Thread Joined Unsuccessfully" :
            "Sectionize Thread Joined Sucessfully") << std::endl;
            
    } else {
            
        std::cout << "Invalid Input" << std::endl;
            
    }
    
    std::cout << ">>> Sifter Function Ended <<<" << std::endl;
}
