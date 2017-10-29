/*


*/

#include <iostream>
#include <string>
#include <vector>

#include <pthread.h>

#include "fence.hpp"
#include "util.hpp"

void* fence_runner(void *arg){

    struct thread_funcs_runner_struct *arg_struct =
        (struct thread_funcs_runner_struct*) arg;
    
    std::vector<std::vector<std::string>> input_vector = 
        arg_struct->input_vector;

    /*
        Do processing
        return message into structure
    */
    
    std::string message;
    for(int i = 0; i < input_vector.size(); i++){
        for(int j = 0; j <input_vector[0].size(); j++){
            message.append(input_vector[i][j] + " ");
        }
    }
    
    arg_struct->final_message = message;

    
    std::cout << ">>> Fence Function Ended <<<" << std::endl;
    pthread_exit(0);
}