/*


*/

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include <math.h>

#include "hill.hpp"
#include "util.hpp"

std::vector<std::vector<std::string> > hill_vectorize(std::string &input){

    std::regex letts_exp("[A-Za-z]");
    std::regex num_exp("[0-9]");
    std::vector<int> indices(split_indices(letts_exp, num_exp, 1, input));
    std::vector<std::vector<std::string>> input_vector(1, std::vector<std::string>(2,""));
                    
    int start = 0;
    int split_index = indices[0];
                    
    // Test if first character in string is a digit or letter   
    // If letter, then split index + 1
    std::string str(1,input[0]);
    if(std::regex_match(str, letts_exp)){
                        
        input_vector[0][0] = input.substr(start, split_index + 1);        
        input_vector[0][1] = input.substr(split_index + 1);        
        
        for(int i = 0; i < input_vector.size(); i++){
            std::cout << "Input Parts: " 
                << input_vector[i][0] << ", "
                << input_vector[i][1] << std::endl;
        }
        
    } else {
                        
        // Swap input parts so that the letter part is first
        // and number part is second in the input vector
        input_vector[0][1] = input.substr(start, split_index);        
        input_vector[0][0] = input.substr(split_index);        
        
        for(int i = 0; i < input_vector.size(); i++){
            std::cout << "Input Parts: " 
                << input_vector[i][0] << ", "
                << input_vector[i][1] << std::endl;
        }
                        
    }    
    
    return input_vector;
}
    
/*
    Valid Expression Examples:
    ABDese123412
    6782yheiAfed
    8902888uhfeahui
*/
bool valid_hill_expr(std::string &input){

    // Store valid regular expressions
    std::string valid_exprs[2]= {
        "([A-Za-z]+)([0-9]+)",
        "([0-9]+)([A-Za-z]+)"
    };
    
    bool has_match = false;
    for(int i = 0; i < 2; i++){
        std::regex rex(valid_exprs[i]);
        if(std::regex_match(input, rex)){
            do_hill_decipher(input);//Move to runner
            has_match = true;
        }
    }    
    
    return has_match;
        
}

void do_hill_decipher(std::string &input){
    
    std::vector<std::vector<std::string>> input_vector(hill_vectorize(input));
       
    int char_reads = 2;
    std::string lett_part = input_vector[0][0];
    std::string num_part = input_vector[0][1];
    
    if(valid_input_parts(lett_part, num_part, char_reads)){
        
        std::string message = read_input(lett_part, num_part, char_reads);
        std::cout << "Message: " << message << std::endl;
    
    } else {
            
        std::cout << "Invalid input parts!!" << std::endl;
            
    }
                
} 

void* hill_runner(void *arg){
    
    std::vector<std::vector<std::string>> *input_vector_ptr = (std::vector<std::vector<std::string>>*) arg;
    std::vector<std::vector<std::string>> input_vector = *input_vector_ptr;
    
    for(int i = 0; i < input_vector.size(); i++){
        std::cout << "Input Parts: " 
                << input_vector[i][0] << ", "
                << input_vector[i][1] << ", "
                << input_vector[i][2] << std::endl;
        
    }

    std::cout << ">>> Hill Function Ended <<<" << std::endl;
    return 0;
}