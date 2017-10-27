/*


*/

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include <pthread.h>

#include "sectionize.hpp"
#include "fence.hpp"
#include "hill.hpp"
#include "pinnacle.hpp"
#include "util.hpp"

std::vector<std::vector<std::string> > vectorize_sections(std::string &input){
    
    std::regex asterisks_exp("\\*");
    std::regex letts_nums_exp("[A-Za-z0-9]+");
    std::vector<int> indices(split_indices(
        asterisks_exp, letts_nums_exp, 6, input));

    std::vector<std::vector<std::string>> input_vector(
        1, std::vector<std::string>(3,""));
        
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
    Valid Sequence Examples:
    *ABDedfe12**sdfEFD32e***38901
    *sefwBAEFe***sefw1234**89023dceg
    **w34r2522*sefewe***wf386AFEDs
    **QWETR789234***sefWEfed**seufg47892
    ***Aeefevf*ahldhlgad**sefAQWERQWr
    ***sefwAGAEg**sefgaqQWE1244*37803yfWEf
    
*/

bool has_valid_asterisks_expr(std::string &input){
    
    std::string valid_exprs[6] = {
       "(\\*{1}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})",
       "(\\*{1}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})",
       "(\\*{2}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})",
       "(\\*{2}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})",
       "(\\*{3}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})",
       "(\\*{3}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})"
    };
    
    
    bool has_match = false;
    for(int i = 0; i < 6; i++){
        std::regex rex(valid_exprs[i]);
        if(std::regex_match(input, rex))
            has_match = true;
    }
	
	return has_match;
}

/*
    Begin 3 new threads:
    Fence, Hill, & Pinnacle
    Vectorize input into a 1 x 3, 2d vector    
*/
void* sectionize_runnable(void *arg){
    
    std::string *new_input_ptr = (std::string*) arg;
    std::string new_input = *new_input_ptr;
    
    if(has_valid_asterisks_expr(new_input)){
        std::vector<std::vector<std::string>> input_vector(
            vectorize_sections(new_input));
        
        static const int NUM_THREADS = 3;
        
        pthread_t fence_thread, hill_thread, pinn_thread;
        pthread_t threads[NUM_THREADS] = {fence_thread, hill_thread, pinn_thread};
        pthread_attr_t thread_attrs[NUM_THREADS];
    
        void* (*thread_runnables[NUM_THREADS]) (void *arg) = {
            fence_runnable,
            hill_runnable,
            pinnacle_runnable
        };
    
        // Initialize threads
        for(int i = 0; i < NUM_THREADS; ++i){
            if(
                pthread_attr_init(&thread_attrs[i]) == 0 &&
                pthread_create(
                    &threads[i], 
                    &thread_attrs[i], 
                    thread_runnables[i], 
                    &input_vector) == 0 &&
                pthread_join(threads[i], NULL) == 0){
            
                printf("Thread's Attributes Initialized, Created, & Joined Sucessfully %d\n", i);
                
            } else {
                
                printf("Thread's Attributes Initialized, Created, & Joined Unsuccessfully %d\n", i);
                
            }
            
            
        }

    } else {
        
        std::cout << "Invalid Input For Fence, Hill, or Pinnacle!" << std::endl;    
        
    }
    
    std::cout << ">>> Sectionize Function Ended <<<" << std::endl;
}
