/*


*/

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include <math.h>
#include <pthread.h>

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
        
        // for(int i = 0; i < input_vector.size(); i++){
        //     std::cout << "Input Parts: " 
        //         << input_vector[i][0] << ", "
        //         << input_vector[i][1] << std::endl;
        // }
        
    } else {
                        
        // Swap input parts so that the letter part is first
        // and number part is second in the input vector
        input_vector[0][1] = input.substr(start, split_index);        
        input_vector[0][0] = input.substr(split_index);        
        
        // for(int i = 0; i < input_vector.size(); i++){
        //     std::cout << "Input Parts: " 
        //         << input_vector[i][0] << ", "
        //         << input_vector[i][1] << std::endl;
        // }
                        
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

    const int VALID_EXPRS = 2;
    std::string valid_exprs[VALID_EXPRS]= {
        "([A-Za-z]+)([0-9]+)",
        "([0-9]+)([A-Za-z]+)"
    };
    
    bool has_match = false;
    for(int i = 0; i < VALID_EXPRS; i++){
        std::regex rex(valid_exprs[i]);
        if(std::regex_match(input, rex))
            has_match = true;
    }
    
    return has_match;

}

std::string do_hill_decipher(std::string &input){
    
    std::vector<std::vector<std::string>> 
        hill_input_vec(hill_vectorize(input));
       
    int char_reads = 2;
    std::string lett_part = hill_input_vec[0][0];
    std::string num_part = hill_input_vec[0][1];
    
    if(valid_input_parts(lett_part, num_part, char_reads)){
        return read_input(lett_part, num_part, char_reads);
    }
    
    
    return "Invalid input for Hill decipher!";

} 

void* hill_runner(void *arg){
    
    struct thread_funcs_runner_struct *arg_struct =
        (struct thread_funcs_runner_struct*) arg;
    
    std::vector<std::vector<std::string>> input_vector = 
        arg_struct->input_vector;
    
    std::string message;
    for(int i = 0; i < input_vector.size(); i++){
        for(int j = 0; j < input_vector[0].size(); j++){
            std::string input = input_vector[i][j];
            if(valid_hill_expr(input)){
                std::string mess = do_hill_decipher(input);
                message.append(mess + " , ");
            }
        }
    }
    
    arg_struct->final_message = message;
    
    std::cout << ">>> Hill Function Ended <<<" << std::endl;
    pthread_exit(0);
}