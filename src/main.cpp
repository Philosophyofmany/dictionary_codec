#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "../include/dictionary_encoder.h"
#include "../include/query_handler.h"

int main() {
    // Define paths for input, output, and result files
    std::string input_file = "data/Column.txt";  // Raw data file path
    std::string encoded_output_file = "data/encoded_column.txt";  // Encoded output data path
    std::string encoding_results_file = "results/encoding_results.txt";  // Dictionary encoding result path
    int num_threads = 4;  // Number of threads to use for multi-threading

    // Debug statement 1: Starting the dictionary encoding
    std::cout << "Starting dictionary encoding..." << std::endl;

    // Call the dictionary encoding function
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> encoded_data;
    dictionary_encode(input_file, encoded_output_file, encoding_results_file, num_threads, dictionary, encoded_data);

    // Debug statement 2: Print out the dictionary after encoding
    std::cout << "Dictionary after encoding:" << std::endl;
    for (const auto& entry : dictionary) {
        std::cout << entry.first << " -> " << entry.second << std::endl;
    }

    // Debug statement 3: Print the encoded data
    std::cout << "Encoded data (IDs): ";
    for (const int encoded_value : encoded_data) {
        std::cout << encoded_value << " ";
    }
    std::cout << std::endl;

    // Create a QueryHandler with the encoded data and dictionary
    QueryHandler query_handler(dictionary, encoded_data);

    // Test (i): Exact match query
    std::string exact_item = "miorceg";  // Replace with an item you'd like to search for
    std::cout << "\nTesting Exact Match Query..." << std::endl;
    std::vector<size_t> exact_match_indices = query_handler.exactMatchQuery(exact_item);

    // Debug statement 4: Show the results of the exact match query
    std::cout << "Exact Match Query for item \"" << exact_item << "\":" << std::endl;
    if (!exact_match_indices.empty()) {
        std::cout << "Item found at indices: ";
        for (size_t idx : exact_match_indices) {
            std::cout << idx << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Item not found in the column." << std::endl;
    }

    // Test (ii): Prefix match query
    std::string prefix = "mi";  // Replace with a prefix you'd like to search for
    std::cout << "\nTesting Prefix Match Query..." << std::endl;
    std::vector<size_t> prefix_match_indices = query_handler.prefixMatchQuery(prefix);

    // Debug statement 5: Show the results of the prefix match query
    std::cout << "Prefix Match Query for prefix \"" << prefix << "\":" << std::endl;
    if (!prefix_match_indices.empty()) {
        std::cout << "Matching items at indices: ";
        for (size_t idx : prefix_match_indices) {
            std::cout << idx << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No items with the specified prefix found in the column." << std::endl;
    }

    return 0;
}
