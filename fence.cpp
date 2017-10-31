/*


*/
#include <fstream>
#include <iostream>
#include <regex>
#include <map>
#include <string>
#include <vector>

#include <pthread.h>

#include "fence.hpp"
#include "util.hpp"

std::vector<std::vector<std::string> > rearrange(std::map<int, int> &column_map, 
    std::vector<std::vector<std::string>> &input_matrix){
    
    int rows = input_matrix.size();
    int cols = input_matrix[0].size();
    
    std::vector<std::vector<std::string>> 
        result_matrix(rows, std::vector<std::string>(cols," "));
        
    for(int i = 0; i < result_matrix.size(); i++){
        for(int j = 0; j < result_matrix[0].size(); j++){
            result_matrix[i][j] = input_matrix[i][column_map[j]];
        }
    }

    return result_matrix;
        
}

/*
    Valid Expression Examples:
    3485291qwerqQWEFewqihf
    123456789wifhuewAWEfeieiwf
    2395ifeQEFeijf
*/
bool valid_fence_expr(std::string &input){
        
    std::vector<std::string> valid_exprs;
    std::string valid_expr_line;
    std::ifstream myfile ("fence_valid_exprs.txt");
    if (myfile.is_open()){
        while (getline (myfile, valid_expr_line)){
            valid_exprs.push_back(valid_expr_line);
        }
        
        myfile.close();
    } 
    
    bool has_match = false;
    for(int i = 0; i < valid_exprs.size(); i++){
        std::regex rex(valid_exprs[i]);
        if(std::regex_match(input, rex))
            has_match = true;
    }
    
    return has_match;
    
}

std::string do_fence_decipher(std::string &input){
    
    // Vectorize input for number part & letter part
    std::vector<std::vector<std::string>> 
        fence_input_vec(vectorize(input));
    
    // std::string lett_part = "ttnaAptMTSUOaodwcoIXknlypETZ";
    // std::string num_part = "4312567";
    
    std::string lett_part = fence_input_vec[0][0];
    std::string num_part = fence_input_vec[0][1];

    // Store corresponding column numbers
    std::map<int, int> column_map;
    for(int i = 0; i < num_part.size(); i++){
        std::string digit(1, num_part[i]);
        column_map.insert(std::pair<int, int>(i, std::stoi(digit) - 1));
    }

    // Get length of input & digit string
    int lett_len = lett_part.size();
    int digit_len = num_part.size();
    
    // Validate the length of the letters with the number of digits
    
    int partition = lett_len / digit_len;
    
    // Variable to read input by
    int read_by = partition;

    //Store input into matrix
    std::vector<std::vector<std::string>> 
        input_matrix(partition, std::vector<std::string>(digit_len, " "));
        
    for(int i = 0; i < partition; i++){
        for(int j = 0; j < digit_len; j++){
            std::string letter(1, lett_part[i + (j * read_by)]);
            input_matrix[i][j] = letter;
        }
    }
    
    // Rearrange input
    std::vector<std::vector<std::string>> 
        result_matrix(rearrange(column_map, input_matrix));
    
    //Create message
    for(int i = 0; i < partition; i++){
        std::cout << "R " << i << ": "; 
        for(int j = 0; j < digit_len; j++){
            std::cout << result_matrix[i][j] << " , ";
        }
        std::cout << std::endl;
    }
    
    return input;
    
}

void* fence_runner(void *arg){

    struct thread_funcs_runner_struct *arg_struct =
        (struct thread_funcs_runner_struct*) arg;
    
    std::vector<std::vector<std::string>> input_vector = 
        arg_struct->input_vector;

    std::string message;
    for(int i = 0; i < input_vector.size(); i++){
        for(int j = 0; j < input_vector[0].size(); j++){
            std::string input = input_vector[i][j];
            if(valid_fence_expr(input)){
                message.append(do_fence_decipher(input) + " , ");
            }
        }
    }
    
    arg_struct->final_message = message;

    
    std::cout << ">>> Fence Function Ended <<<" << std::endl;
    pthread_exit(0);
}