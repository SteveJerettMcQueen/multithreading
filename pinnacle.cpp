/*


*/

#include <iostream>
#include <string>
#include <vector>

#include <pthread.h>

#include "hill.hpp"
#include "pinnacle.hpp"
#include "util.hpp"

std::string do_pinn_decipher(std::string &input){
    
    std::vector<std::vector<std::string>> 
        pinn_input_vec(hill_vectorize(input));
       
    int char_reads = 3;
    std::string lett_part = pinn_input_vec[0][0];
    std::string num_part = pinn_input_vec[0][1];
    
    if(valid_input_parts(lett_part, num_part, char_reads)){
        return read_input(lett_part, num_part, char_reads);
    }
    
    
    return "Invalid input for Pinnacle decipher!";
    
}

void* pinnacle_runner(void *arg){
    
    struct thread_funcs_runner_struct *arg_struct =
        (struct thread_funcs_runner_struct*) arg;
    
    std::vector<std::vector<std::string>> input_vector = 
        arg_struct->input_vector;

    std::string message;
    for(int i = 0; i < input_vector.size(); i++){
        for(int j = 0; j < input_vector[0].size(); j++){
            std::string input = input_vector[i][j];
            if(valid_hill_expr(input)){
                std::string mess = do_pinn_decipher(input);
                message.append(mess + " , ");
            }
        }
    }
    
    arg_struct->final_message = message;
    
    
    std::cout << ">>> Pinnacle Function Ended <<<" << std::endl;
    pthread_exit(0);
}