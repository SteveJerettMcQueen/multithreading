/*


*/

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "sifter.hpp"

bool isValidInput(std::string &input){
    
	std::string regex_str = "(\\*{1,3}[A-Za-z0-9]+){1,3}";
	std::regex rex(regex_str); 
	
	return (std::regex_match(input, rex));

}

//Function pointer
void* sifter(void *arg){
    
    std::string *input_ptr = (std::string*) arg;
    std::string input = *input_ptr;
    
    // //Tokenize the input by removing whitespaces
    // std::string tokInput;
    
    // //Validate the input
    // if(isValidInput(tokInput)) {
        
    //     //Decode(sectionize) the input
        
        
    // } else {
        
        
        
    // }
    
    std::cout << ">>> Sifter Function Ended <<<" << std::endl;
    pthread_exit(0);
}
