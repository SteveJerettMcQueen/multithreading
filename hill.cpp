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

/*
    Valid Expression Examples:
    ABDese123412
    6782yheiAfed
    8902888uhfeahui
*/
bool valid_hill_expr(std::string &input){

    const int VALID_EXPRS = 2;
    std::string valid_exprs[VALID_EXPRS] = {
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
        hill_input_vec(vectorize(input));
       
    int char_reads = 2;
    std::string lett_part = hill_input_vec[0][0];
    std::string num_part = hill_input_vec[0][1];
    
    if(valid_input_parts(lett_part, num_part, char_reads)){
        
        return read_input(lett_part, num_part, char_reads);
        
    } else {
        
        return "Invalid Input Parts For Hill Decipher!";
        
    }
} 

void* hill_runner(void *arg){
    
    struct thread_funcs_runner_struct *arg_struct =
        (struct thread_funcs_runner_struct*) arg;
    
    std::vector<std::vector<std::string>> input_vector = 
        arg_struct->input_vector;
    
    std::string message = "Hill ->\n";
    for(int i = 0; i < input_vector.size(); i++){
        for(int j = 0; j < input_vector[0].size(); j++){
            std::string input = input_vector[i][j];
            if(valid_hill_expr(input)){
                message.append(do_hill_decipher(input) + "\n");
            } else {
                message.append("Invalid Hill Expression!\n");
            }
        }
    }
    
    arg_struct->final_message = message;
    
    pthread_exit(0);
}