#include <fstream>
#include <iostream>
#include <string>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sifter.hpp"

int main(){
    
    std::string input;
    while(input != ":exit"){
        
        std::cout << "Please Enter The Cipher Input or Enter ':exit' To Exit Program: ";
        std::getline(std::cin, input);
        
        if(input == ":exit"){
            
            std::cout << ">>> Program Exit <<<" << std::endl;
            break;
            
        // Launch thread    
        } else {
            
            // Thread ID
            pthread_t sifter_thread;
        
            // Thread attributes
            pthread_attr_t sft_attr;
            pthread_attr_init(&sft_attr);
            
            // Create thread
            pthread_create(&sifter_thread, &sft_attr, sifter_runner, &input);
            
            // Suspend wait during execution
            pthread_join(sifter_thread, NULL);
            
        }
        
    } 
    
    return 0;
    
}

