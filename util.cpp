/*


*/

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "util.hpp"

std::vector<int> split_indices(std::regex &rex, std::regex &rex2, 
    int max_splits, std::string &input){
    
    std::vector<int> split_indices;
    
    int last_index = input.size() - 1;
    for(int i = 0; i < input.size(); i++){
        
        int current_index = i;
        int next_index = i + 1;
        
        //Convert single character to string for regex
        std::string str(1,input[current_index]);
        std::string str2(1,input[next_index]);
        
        if(std::regex_match(str, rex) && 
            std::regex_match(str2, rex2)) {
                
            if(next_index == last_index){
                
                //Store current & last index
                split_indices.push_back(current_index);
                split_indices.push_back(last_index);
                
            } else {
                
                //Store current index
                split_indices.push_back(current_index);
            }    
                
                
        } else if(std::regex_match(str, rex2) && 
            std::regex_match(str2, rex)) {
            
            //Store next index
            split_indices.push_back(next_index);
            
        } 
        
    }
    
    // Max number of indices stored in vector based from regex
    if(split_indices.size() != max_splits){
        split_indices.push_back(last_index);
    }
    
    for(int i = 0; i < input.size(); i++){
        std::cout << "index : " << i << " : " << input[i] << std::endl;
    }
    
    for(int i = 0; i < split_indices.size(); i++){
        std::cout << "split index: " << split_indices[i] << std::endl;
    }
    
    
    return split_indices;
    
}