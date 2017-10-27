/*


*/

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "hill.hpp"
#include "util.hpp"


std::vector<std::vector<std::string> > vectorize_hill(std::string &input){
    
    
}
    
/*
    Valid Sequence Examples
    ABDese123412
    6782yheiAfed
    8902888uhfeahui
*/
bool is_valid_hill_expr(std::string &input){
    
    std::string valid_exprs[2]= {
        "([A-Za-z]+)([0-9]+)",
        "([0-9]+)([A-Za-z]+)"
    };
    
    bool has_match = false;
    
    for(int i = 0; i < 2; i++){
        
        std::regex rex(valid_exprs[i]);
        if(std::regex_match(input, rex)){
            
            std::regex r("[A-Za-z]");
            std::regex r2("[0-9]");
            std::vector<int> indices(split_indices(r, r2, 1, input));
            
            // Update indices vector
            std::vector<std::vector<std::string>> input_vector(1, std::vector<std::string>(2,""));
            
            int start = 0;
            int split_index = indices[0];
            
            /*
                Test if first character in string is digit or letter   
                if character then split index + 1
            */  
            std::string str(1,input[0]);
            if(std::regex_match(str, r)){
                
                std::string input_part_1(input.substr(start, split_index + 1));
                input_vector[0][0] = input_part_1;        
                    
                std::string input_part_2(input.substr(split_index + 1));
                input_vector[0][1] = input_part_2;        

                for(int i = 0; i < input_vector.size(); i++){
                    std::cout << "Input Parts: " 
                        << input_vector[i][0] << ", "
                        << input_vector[i][1] << std::endl;
                }

            } else {
                
                std::string input_part_1(input.substr(start, split_index));
                input_vector[0][1] = input_part_1;        
                    
                std::string input_part_2(input.substr(split_index));
                input_vector[0][0] = input_part_2;        

                for(int i = 0; i < input_vector.size(); i++){
                    std::cout << "Input Parts: " 
                        << input_vector[i][0] << ", "
                        << input_vector[i][1] << std::endl;
                }
                
            }
            
            std::regex r3("[A-Za-z]+");
            std::regex r4("[0-9]+");
            
            if(are_valid_input_parts(r3, r4, input_vector[0][0], input_vector[0][1])){
                
                //Do Matrix Multiplication
                
            }

        } 

    }
    
	return has_match;
}


bool are_valid_input_parts(std::regex &letts_exp, std::regex &num_exp,
    std::string &input_part_1, std::string &input_part_2){
    
    bool is_valid_input_part_1 = false;
    bool is_valid_input_part_2 = false;
    
    bool is_letts_exp = (std::regex_match(input_part_1, letts_exp));
    bool is_part_1_greater = (input_part_1.size() >= 4);
    bool is_part_1_even = (input_part_1.size() % 2 == 0);

    bool is_num_exp = (std::regex_match(input_part_2, num_exp));
    bool is_part_2_greater = (input_part_2.size() >= 4);
    bool is_part_2_even = (input_part_2.size() % 2 == 0);

    if(is_letts_exp){
        
        std::cout << "p1: Is Letter Exp!" << std::endl;        
                
        if(is_part_1_even){
                    
            is_valid_input_part_1 = true;
            
            std::cout << "p1: Is Even!" << std::endl;             
                    
        } else {
                    
            is_valid_input_part_1 = false;
            
            std::cout << "p1: Is Not Even!" << std::endl;         

        }
                
    } else {
                
        std::cout << "p1: Is Number Exp!" << std::endl;        
                
        if(is_part_1_greater){
                    
            is_valid_input_part_1 = true;
            
            std::cout << "p1: Is greater than or equal to 4!" << std::endl; 
            
        } else {
            
            is_valid_input_part_1 = false;
            
            std::cout << "p1: Is not greater than or equal to 4!" << std::endl; 

        }
    }
            
    if(is_num_exp){
                
        std::cout << "p2: Is Number Exp!" << std::endl;        
                
        if(is_part_2_greater){
                    
            is_valid_input_part_2 = true;
            
            std::cout << "p2: Is greater than or equal to 4!" << std::endl;        
                    
        } else {
                    
            is_valid_input_part_2 = false;
            
            std::cout << "p2: Is not greater than or equal to 4!" << std::endl;        
        }
                
    } else {
        
        std::cout << "p2: Is Letter Exp!" << std::endl;        
        
        if(is_part_2_even){
                    
            is_valid_input_part_2 = true;
            
            std::cout << "p2: Is Even!" << std::endl;         

        } else {
                    
            is_valid_input_part_2 = false;
            
            std::cout << "p2: Is Not Even!" << std::endl;        

        }
    }
            
    bool are_both_valid = (is_valid_input_part_1 && is_valid_input_part_2);
    std::cout << "Are Valid Inputs ? " << ((are_both_valid) ? "Yes":"No") << std::endl;
    return are_both_valid;
    
}


void* hill_runnable(void *arg){
    
    std::vector<std::vector<std::string>> *input_vector_ptr = (std::vector<std::vector<std::string>>*) arg;
    std::vector<std::vector<std::string>> input_vector = *input_vector_ptr;
    
    for(int i = 0; i < input_vector.size(); i++){
        std::cout << "Input Parts: " << input_vector[i][0] << ", "
                  << input_vector[i][1] << ", "
                  << input_vector[i][2] << std::endl;
        
    }
    
    std::cout << ">>> Hill Function Ended <<<" << std::endl;
    return 0;
}