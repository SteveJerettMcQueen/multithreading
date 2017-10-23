#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "threads.hpp"
#include "sifter.hpp"
#include "fence.hpp"
#include "hill.hpp"
#include "pinnacle.hpp"

int main(){

    std::string input;
    std::cout << "Please Enter The Cipher Input: ";
    std::getline(std::cin, input);
    std::cout << "The Cipher Input You Entered is: ( " << input << " )" << std::endl;

    // Thread ID
    pthread_t SIFTER_THREAD_ID = threadconstants::SIFTER_THREAD;
    
    // Thread attributes
    pthread_attr_t sft_attr;
    std::cout << ((pthread_attr_init(&sft_attr)) ?
        "Sifter Thread Attributes Initialize Unsuccessfully" :
        "Sifter Thread Attributes Initialize Sucessfully") << std::endl;
    
    // Create thread
    std::cout << ((pthread_create(&SIFTER_THREAD_ID, &sft_attr, sifter, &input)) ?
        "Sifter Thread Created Unsuccessfully" :
        "Sifter Thread Created Sucessfully") << std::endl;
    
    //Suspend execution, wait
    std::cout << ((pthread_join(SIFTER_THREAD_ID, NULL)) ? 
        "Sifter Thread Joined Unsuccessfully" :
        "Sifter Thread Joined Sucessfully") << std::endl;
    
    return 0;
    
}

