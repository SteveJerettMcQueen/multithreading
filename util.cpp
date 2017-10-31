/*


*/

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include <math.h>

#include "util.hpp"

std::vector<std::vector<int> > multiply_matrices(std::vector<std::vector<int>> &a, std::vector<std::vector<int>> &b){
    
    int a_row_len = a.size();
    int a_col_len = a[0].size();
    
    int b_row_len = b.size();
    int b_col_len = b[0].size();
    
    std::vector<std::vector<int>> c(a_row_len, std::vector<int>(b_col_len, 0));
    if(a_col_len == b_row_len)
        for(int i = 0; i < a_row_len; i++)
            for(int j = 0; j < b_col_len; j++)
                for(int k = 0; k < a_col_len; k++)
                    // std::cout << "( " << a[i][k] << " x " << b[k][j] << " = " << a[i][k] * b[k][j] << " ) ";
                    c[i][j] += a[i][k] * b[k][j];
        
        // Modulo the result
        for(int i = 0; i < c.size(); i++)
            for(int j = 0; j < c[0].size(); j++)
                c[i][j] %= 26;
    
    return c;
}

std::string read_input(std::string &input, std::string &input2, int char_reads){
            
    char alphabets[26] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    
    // Store corresponding numbers & letters in a map
    std::map<char, int> alphabet_map;
    std::map<int, char> number_map;        
        
    for(int i = 0; i < 26; i++){
        alphabet_map.insert(std::pair<char, int> (alphabets[i], i));
        number_map.insert(std::pair<int, char> (i, alphabets[i]));
    }    
            
    std::string message;
    std::string lett_part = input;
    std::string num_part = input2;
                        
    // Get first "n" digits from number part
    num_part = num_part.substr(0, pow(char_reads, 2));
       
    // Convert number part into a n x n matrix
    std::vector<std::vector<int>> num_part_vector(char_reads, std::vector<int>(char_reads,0));
    int p_index = 0;
    for(int i = 0; i < num_part_vector.size(); i++){
        for(int j = 0; j < num_part_vector[0].size(); j++){
            std::string str(1,num_part[p_index]);
            num_part_vector[i][j] = std::stoi(str);
            p_index +=1;
        }
    }
                        
    std::vector<std::vector<int>> lett_part_vector(lett_part.size(), std::vector<int>(1,0));
    for(int i = 0; i < lett_part_vector.size(); i += char_reads){
            
        std::vector<std::vector<int>> sub_vector(char_reads, std::vector<int>(1,0));
        for(int j = i; j < (i + char_reads); j++){
            char lett = std::toupper(lett_part[j]);
            lett_part_vector[j][0] = alphabet_map[lett];
            sub_vector[(j % char_reads)][0] = lett_part_vector[j][0];
        }    
                
        // Do matrix multiplication
        std::vector<std::vector<int>> matrix(multiply_matrices(num_part_vector, sub_vector));
                
        // Create message
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[0].size(); j++){
                // std::cout << "[ " << (matrix[i][j]) << " : " << number_map[matrix[i][j]] << " ]" << std::endl;
                std::string str(1,number_map[matrix[i][j]]);
                message.append(str + " ");
            }
        }
                            
        // std::cout << "#####################################" << std::endl;
        
    }
                    
            
    return message;
}

std::string remove_white_space(std::string &input){
    
    input.erase(
        std::remove_if(
            input.begin(), 
            input.end(), 
            std::bind(
                std::isspace<char>, 
                std::placeholders::_1, 
                std::locale::classic() 
            )
        ), 
        
        input.end()

        );
        
    return input;
    
}

std::vector<int> split_indices(std::regex &rex, std::regex &rex2, int max_splits, std::string &input){
    
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
    
    // for(int i = 0; i < input.size(); i++){
    //     std::cout << "index : " << i << " : " << input[i] << std::endl;
    // }
    
    // for(int i = 0; i < split_indices.size(); i++){
    //     std::cout << "split index: " << split_indices[i] << std::endl;
    // }
    
    
    return split_indices;
    
}

bool valid_input_parts(std::string &p1, std::string &p2, int char_reads){
    
    std::regex letts_exp("[A-Za-z]+");
    std::regex num_exp("[0-9]+");
    
    bool valid_p1 = false;
    bool valid_p2 = false;
    
    bool is_letts_exp = (std::regex_match(p1, letts_exp));
    bool is_p1_greater = (p1.size() >= pow(char_reads,2));
    bool is_p1_divis_by = (p1.size() % char_reads == 0);

    bool is_num_exp = (std::regex_match(p2, num_exp));
    bool is_p2_greater = (p2.size() >= pow(char_reads,2));
    bool is_p2_divis_by = (p2.size() % char_reads == 0);

    // Letter expression
    if(is_letts_exp){
        
        if(is_p1_divis_by){
                    
            valid_p1 = true;
            
        } else {
                    
            valid_p1 = false;
            
        }
                
    } else {
                
        if(is_p1_greater){
                    
            valid_p1 = true;
            
        } else {
            
            valid_p1 = false;
            
        }
    }
            
    // Number expression        
    if(is_num_exp){
                
        if(is_p2_greater){
                    
            valid_p2 = true;
            
        } else {
                    
            valid_p2 = false;
            
        }
                
    } else {
        
        if(is_p2_divis_by){
                    
            valid_p2 = true;
            
        } else {
                    
            valid_p2 = false;
            
        }
    }
            
    return (valid_p1 && valid_p2);
    
}

std::vector<std::vector<std::string> > vectorize(std::string &input){

    std::regex letts_exp("[A-Za-z]");
    std::regex num_exp("[0-9]");
    std::vector<int> indices(split_indices(letts_exp, num_exp, 1, input));
    std::vector<std::vector<std::string>> input_vector(1, std::vector<std::string>(2,""));
                    
    int start = 0;
    int split_index = indices[0];
                    
    // Test if first character in string is a digit or letter   
    // If letter, then split index + 1
    std::string str(1,input[0]);
    if(std::regex_match(str, letts_exp)){
                        
        input_vector[0][0] = input.substr(start, split_index + 1);        
        input_vector[0][1] = input.substr(split_index + 1);        
        
        // for(int i = 0; i < input_vector.size(); i++){
        //     std::cout << "Input Parts: " 
        //         << input_vector[i][0] << ", "
        //         << input_vector[i][1] << std::endl;
        // }
        
    } else {
                        
        // Swap input parts so that the letter part is first
        // and number part is second in the input vector
        input_vector[0][1] = input.substr(start, split_index);        
        input_vector[0][0] = input.substr(split_index);        
        
        // for(int i = 0; i < input_vector.size(); i++){
        //     std::cout << "Input Parts: " 
        //         << input_vector[i][0] << ", "
        //         << input_vector[i][1] << std::endl;
        // }
                        
    }    
    
    return input_vector;
}
    