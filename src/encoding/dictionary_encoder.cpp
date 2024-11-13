#include "../../include/dictionary_encoder.h"
#include "../../include/multi_threading.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <mutex>

// Function to encode the data column into dictionary encoding
void dictionary_encode(const std::string& input_file, const std::string& encoded_output_file, const std::string& encoding_results_file, int num_threads, std::unordered_map<std::string, int>& dictionary, std::vector<int>& encoded_data) {
    std::ifstream infile(input_file);
    std::ofstream encoded_outfile(encoded_output_file);
    std::ofstream results_outfile(encoding_results_file);
    std::vector<std::string> data;
    std::string line;

    // Read data from the input file (Column.txt)
    while (getline(infile, line)) {
        data.push_back(line);  // Collect all lines in a vector
    }

    // Call the multi-threaded dictionary encoding function
    dictionary_encode_multi_threaded(data, dictionary, num_threads);

    // Populate encoded_data based on dictionary
    for (const auto& item : data) {
        encoded_data.push_back(dictionary[item]);
    }

    // Write the dictionary and encoded data to respective output files

    // Write dictionary to encoding_results.txt (results directory)
    if (results_outfile.is_open()) {
        results_outfile << "Dictionary:\n";
        for (const auto& entry : dictionary) {
            results_outfile << entry.first << " -> " << entry.second << "\n"; // Write dictionary entry
        }
        results_outfile.close();
    } else {
        std::cerr << "Error opening file: " << encoding_results_file << std::endl;
    }

    // Write the encoded column data to encoded_column.txt (data directory)
    if (encoded_outfile.is_open()) {
        for (int encoded_value : encoded_data) {
            encoded_outfile << encoded_value << "\n"; // Write encoded data (IDs)
        }
        encoded_outfile.close();
    } else {
        std::cerr << "Error opening file: " << encoded_output_file << std::endl;
    }

    std::cout << "Dictionary encoding complete. Results saved to:\n"
              << " - " << encoded_output_file << "\n"
              << " - " << encoding_results_file << std::endl;
}
