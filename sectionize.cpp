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


std::vector<std::vector<std::string> > vectorize(std::string &input){
    
    std::regex asterisks_exp("\\*");
    std::regex letts_nums_exp("[A-Za-z0-9]+");
    std::vector<int> indices;
    
    int last_index = input.length() - 1;
    for(int i = 0; i < input.length(); i++){
        
        int current_index = i;
        int next_index = i + 1;
        
        //Convert single character to string for regex
        std::string str(1,input[current_index]);
        std::string str2(1,input[next_index]);
        
        if(std::regex_match(str, asterisks_exp) && 
            std::regex_match(str2, letts_nums_exp)) {
                
            if(next_index == last_index){
                
                //Store current & last index
                indices.push_back(current_index);
                indices.push_back(last_index);
                
            } else {
                
                //Store current index
                indices.push_back(current_index);
            }    
                
                
        } else if(std::regex_match(str, letts_nums_exp) && 
            std::regex_match(str2, asterisks_exp)) {
            
            //Store next index
            indices.push_back(next_index);
            
        } 
        
    }
    
    int max_indices = 6;
    if(indices.size() != max_indices){
        indices.push_back(last_index);
    }
    
    // for(int i = 0; i < input.length(); i++){
    //     std::cout << "str @ : " << i << " : " << input[i] << std::endl;
    // }
    
    // for(int i = 0; i < indices.size(); i++){
    //     std::cout << "index: " << indices[i] << std::endl;
    // }

    std::vector<std::vector<std::string>> input_vector(1, std::vector<std::string>(3,""));
    last_index = indices.size() - 2;
    for(int i = 0; i < indices.size(); i += 2){
        
        int current_index = i;  // 0, 2, 4
        int next_index = i + 1; // 1, 3, 
        
        if(current_index != last_index){
            
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

bool has_valid_asterisks(std::string &input){
    
    /*
        Valid Sequence Examples:
        *ABDedfe12**sdfEFD32e***38901
        *sefwBAEFe***sefw1234**89023dceg
        **w34r2522*sefewe***wf386AFEDs
        **QWETR789234***sefWEfed**seufg47892
        ***Aeefevf*ahldhlgad**sefAQWERQWr
        ***sefwAGAEg**sefgaqQWE1244*37803yfWEf
    
    */
    
    static const int NUM_VALID_EXPR = 6;
    
    std::string valid_exprs[NUM_VALID_EXPR] = {
       "(\\*{1}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})",
       "(\\*{1}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})",
       "(\\*{2}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})",
       "(\\*{2}[A-Za-z0-9]+{1})(\\*{3}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})",
       "(\\*{3}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})",
       "(\\*{3}[A-Za-z0-9]+{1})(\\*{2}[A-Za-z0-9]+{1})(\\*{1}[A-Za-z0-9]+{1})"
    };
    
    
    bool has_match = false;
    for(int i = 0; i < NUM_VALID_EXPR; i++){

        std::regex rex(valid_exprs[i]);
        if(std::regex_match(input, rex)){
            has_match = true;
        }
        
    }
	
	return has_match;
}

void* sectionize_runnable(void *arg){
    
    std::string *new_input_ptr = (std::string*) arg;
    std::string new_input = *new_input_ptr;
    
    //Sectionize input into a 1 x 3, 2D_vector
    std::vector<std::vector<std::string> > input_vector(1, std::vector<std::string>(3,""));
    
    /*
        Add content to vector ....
    */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
        Begin 3 new threads:
        Fence, Hill, & Pinnacle
        
    */
    
    static const int NUM_THREADS = 3;
    
    pthread_t fence_thread, hill_thread, pinn_thread;
    pthread_t threads[NUM_THREADS] = {fence_thread, hill_thread, pinn_thread};
    pthread_attr_t thread_attrs[NUM_THREADS];

    void* (*thread_runnables[NUM_THREADS]) (void *arg) = {
        fence_runnable,
        hill_runnable,
        pinnacle_runnable
    };

    //Initialize threads
    // for(int i = 0; i < NUM_THREADS; ++i){
    //     if(
    //         pthread_attr_init(&thread_attrs[i]) == 0 &&
    //         pthread_create(
    //             &threads[i], 
    //             &thread_attrs[i], 
    //             thread_runnables[i], 
    //             &input_vector) == 0 &&
    //         pthread_join(threads[i], NULL) == 0){
        
    //         printf("Thread Attributes Initialized, Created, & Joined Sucessfully %d\n", i);
            
    //     } else {
            
    //         printf("Thread Attributes Initialized, Created, & Joined Unsuccessfully %d\n", i);
            
    //     }
        
        
    // }

    std::cout << ">>> Sectionize Function Ended <<<" << std::endl;
}
