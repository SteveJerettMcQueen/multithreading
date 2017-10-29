/*


*/

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include <pthread.h>

#include "sectionize.hpp"
#include "fence.hpp"
#include "hill.hpp"
#include "pinnacle.hpp"
#include "util.hpp"

std::vector<std::vector<std::string> > section_vectorize(std::string &input){
    
    std::regex asterisks_exp("\\*");
    std::regex letts_nums_exp("[A-Za-z0-9]+");
    std::vector<int> indices(split_indices(asterisks_exp, letts_nums_exp, 6, input));
    std::vector<std::vector<std::string>> input_vector(1, std::vector<std::string>(3,""));
        
    for(int i = 0; i < indices.size(); i += 2){
        
        int current_index = i;  // 0, 2, 4
        int next_index = i + 1; // 1, 3, 
        
        if(current_index != indices.size() - 2){
            
            int start = indices[current_index] + 1;
            int end = indices[next_index] - 1; 
    
            std::string input_part(input.substr(start,(end - start) + 1));
            input_vector[0][i/2] = input_part;
                
            // std::cout << "Current indx: " << current_index << std::endl;
            // std::cout << "Next indx: " << next_index << std::endl;
            // std::cout << "Start: " << start << std::endl;
            // std::cout << "End: " << end << std::endl;
            // std::cout << "Length: " << (end - start) + 1 << std::endl;
            // std::cout << "Input Part: " << i/2 << " : " << input_part << std::endl;
        
        } else {
            
            int start = indices[current_index] + 1; 
            std::string input_part(input.substr(start));
            input_vector[0][(i/2)] = input_part;
            
            // std::cout << "Current indx: " << current_index << std::endl;
            // std::cout << "Start: " << start << std::endl;
            // std::cout << "Input Part: " << i/2 << " : " << input_part << std::endl;
            
        }
            
    }    
    
    return input_vector;
    
}


/*
    Valid Expression Examples:
    *ABDedfe12**sdfEFD32e***38901
    *sefwBAEFe***sefw1234**89023dceg
    **w34r2522*sefewe***wf386AFEDs
    **QWETR789234***sefWEfed**seufg47892
    ***Aeefevf*ahldhlgad**sefAQWERQWr
    ***sefwAGAEg**sefgaqQWE1244*37803yfWEf
    
*/

bool valid_asterisks_expr(std::string &input){
    
    const int NUM_VALID_EXPRS = 6;
    std::string valid_exprs[NUM_VALID_EXPRS] = {
       "(\\*{1}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})",
       "(\\*{1}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})",
       "(\\*{2}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})",
       "(\\*{2}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})",
       "(\\*{3}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})",
       "(\\*{3}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})"
    };
    
    
    bool has_match = false;
    for(int i = 0; i < NUM_VALID_EXPRS; i++){
        std::regex rex(valid_exprs[i]);
        if(std::regex_match(input, rex))
            has_match = true;
    }
	
	return has_match;
}

void* sectionize_runner(void *arg){
    
    struct sec_runner_struct *arg_struct =
        (struct sec_runner_struct*) arg;
    
    std::string new_input = arg_struct->input;
    
    // std::string *new_input_ptr = (std::string*) arg;
    // std::string new_input = *new_input_ptr;
    
    std::ostringstream os;
    
    if(valid_asterisks_expr(new_input)){

        const int NUM_THREADS = 3;
        
        // Array of threads
        pthread_t threads[NUM_THREADS];
        
        // Array of thread's attributes
        pthread_attr_t thread_attrs[NUM_THREADS];
    
        // Array of thread's function structures
        struct thread_funcs_runner_struct struct_args[NUM_THREADS];

        // Array of thread function runners
        void* (*thread_runners[NUM_THREADS]) (void *arg) = {
            fence_runner, hill_runner, pinnacle_runner
        };

        // Initialize threads
        for(int i = 0; i < NUM_THREADS; i++){
            
            struct_args[i].input_vector = section_vectorize(new_input);
            int result = pthread_attr_init(&thread_attrs[i]);
            int result2 = pthread_create(&threads[i], &thread_attrs[i], 
                thread_runners[i], &struct_args[i]);
            
            if(result == 0 && result2 == 0){
            
                os << "Thread " << i << " Attributes Initialized, Created Sucessfully" << std::endl;
                arg_struct->status = os.str();

            } else {
                
                os << "Thread " << i << " Attributes Initialized, Created Unsucessfully" << std::endl;
                arg_struct->status = os.str();
                
            }
        }
        
        
        // Join threads
        for(int i = 0; i < NUM_THREADS; i++){
            if(pthread_join(threads[i], NULL) == 0){
                
                os << "Thread " << i << " Joined Successfully" << std::endl;
                arg_struct->status = os.str();
                
                std::cout << "Final Message: " << struct_args[i].final_message << std::endl;
                
            } else { 
                
                os << "Thread " << i << " Joined Unsuccessfully" << std::endl;
                arg_struct->status = os.str();                
            }
        }

    } else {
        
        os << "Input: ( " << new_input << " ) is invalid for Fence, Hill, & Pinnacle!" << std::endl;
        arg_struct->status = os.str();
        
    }
    
    std::cout << ">>> Sectionize Function Ended <<<" << std::endl;
}
