#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fence.hpp"
#include "hill.hpp"
#include "sifter.hpp"
#include "pinnacle.hpp"
#include "sectionize.hpp"

int main(){

    std::string input;
    std::cout << "Please Enter The Cipher Input: ";
    std::getline(std::cin, input);
    std::cout << "The Cipher Input You Entered is: ( " << input << " )" << std::endl;
    std::cout << "Valid Hill Expression: " << valid_hill_expr(input) << std::endl;

    // // /*
    // //     Begin Sifter Thread
    // // */

    // // Thread ID
    // pthread_t sifter_thread;

    // // Thread attributes
    // pthread_attr_t sft_attr;
    // std::cout << ((pthread_attr_init(&sft_attr)) ?
    //     "Sifter Thread Attributes Initialize Unsuccessfully" :
    //     "Sifter Thread Attributes Initialize Sucessfully") << std::endl;
    
    // // Create thread
    // std::cout << ((pthread_create(&sifter_thread, &sft_attr, sifter_runner, &input)) ?
    //     "Sifter Thread Created Unsuccessfully" :
    //     "Sifter Thread Created Sucessfully") << std::endl;
    
    // // Suspend execution, wait
    // std::cout << ((pthread_join(sifter_thread, NULL)) ? 
    //     "Sifter Thread Joined Unsuccessfully" :
    //     "Sifter Thread Joined Sucessfully") << std::endl;
    
    // return 0;
    
}

