#include <iostream>
#include "../include/dictionary_encoder.h"

int main() {
    // Define the paths for input and output files
    std::string input_file = "data/Column.txt";  // Path to the input raw data file
    std::string encoded_output_file = "data/encoded_column.txt";  // Path for the encoded output data (overwrites the input file)
    std::string encoding_results_file = "results/encoding_results.txt";  // Path to save the dictionary encoding results
    int num_threads = 4;  // Number of threads to use for multi-threading during encoding

    // Call the dictionary encoding function
    dictionary_encode(input_file, encoded_output_file, encoding_results_file, num_threads);

    return 0;
}
