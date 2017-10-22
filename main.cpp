#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sifter.h"
#include "fence.h"
#include "hill.h"
#include "pinnacle.h"

int main(){

    std::string input;
    std::cout << "Please Enter The Cipher Message: ";
    std::getline(std::cin, input);
    
    std::cout << "The Cipher Message You Entered is: ( " << input << " )" << std::endl;
    
    
    std::cout << "Is it a valid message?: " << ((isValidMessage(input)) ? "True" : "False") << std::endl;
    
    return 0;
    
}

