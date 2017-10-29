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
    std::cout << "The Ciphered Input You Entered is: ( " << input << " )" << std::endl;

    // Thread ID
    pthread_t sifter_thread;

    // Thread attributes
    pthread_attr_t sft_attr;
    pthread_attr_init(&sft_attr);
    
    // Create thread
    pthread_create(&sifter_thread, &sft_attr, sifter_runner, &input);
    
    // Suspend wait during execution
    pthread_join(sifter_thread, NULL);
    
    return 0;
    
}

