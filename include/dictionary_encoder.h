#ifndef DICTIONARY_ENCODER_H
#define DICTIONARY_ENCODER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <string>

// Declare the dictionary_encode function
void dictionary_encode(const std::string& input_file, const std::string& encoded_output_file, const std::string& encoding_results_file, int num_threads, std::unordered_map<std::string, int>& dictionary, std::vector<int>& encoded_data);

#endif  // DICTIONARY_ENCODER_H
