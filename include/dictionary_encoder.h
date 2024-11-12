#ifndef DICTIONARY_ENCODER_H
#define DICTIONARY_ENCODER_H

#include <string>

// Declare the dictionary_encode function
void dictionary_encode(const std::string& input_file, const std::string& encoded_output_file, const std::string& encoding_results_file, int num_threads);

#endif  // DICTIONARY_ENCODER_H
