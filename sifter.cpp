/*


*/

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "sifter.h"


bool isValidMessage(std::string &message){
    
	// Pattern
	std::string regex_str = "(\\*{1,3}[A-Za-z0-9]+){1,3}";
	std::regex rex(regex_str); 
    
	// regex_match function matches string a against regex b
	if (std::regex_match(message, rex)){
	    
// 		std::cout << "' " << message << " ' matches regular expression ' " << regex_str << " '" << std::endl;
        return true;
        
	} else {
	    
	   // std::cout << "' " << message << " ' does not match regular expression ' " << regex_str << " '" << std::endl;
	    return false;
	}
	
// 	// regex_match function for matching a range in message against regex 
// 	if (std::regex_match(message.begin(), message.end(), rex)){
	    
// 		std::cout << "' " << message << " ' matches regular expression ' " << regex_str << " '" << std::endl;
// 		return true;
		
// 	} else {
	    
// 	    return false;
// 	}

}

std::vector<std::vector<std::string> > sectionize(std::string &message){
    std::vector<std::vector<std::string> > messageVector;
    
    
    return messageVector;
}


std::string sifter(std::string &message){
    
    //Tokenize the message by removing whitespaces
    std::string tokzMessage;
    
    //Validate the message
    if(isValidMessage(tokzMessage)) {
        
        //Sectionize the message
        
    } else {
        
        
        
    }
    
    return message;
}


