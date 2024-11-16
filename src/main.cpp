#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "../include/dictionary_encoder.h"
#include "../include/query_handler.h"
#include "../include/vanilla_search.h"
#include "../include/performance_test.h"


int main() {
    // Define paths for input, output, and result files
    std::string input_file = "data/Column.txt";  // Raw data file path
    std::string encoded_output_file = "data/encoded_column.txt";  // Encoded output data path
    std::string encoding_results_file = "results/encoding_results.txt";  // Dictionary encoding result path
    std::string performance_results_file = "results/performance_results.txt";  // Performance results file path

    // Ask the user if they want to run the performance test
    char performance_choice;
    std::cout << "Do you want to run the performance test? (y/n): ";
    std::cin >> performance_choice;

    if (performance_choice == 'y' || performance_choice == 'Y') {
        std::cout << "Running performance test...\n";
        test_performance(input_file, performance_results_file);
    }

    // Load raw data for vanilla search
    std::vector<std::string> data_column;
    std::ifstream infile(input_file);
    if (!infile.is_open()) {
        std::cerr << "Error opening input file: " << input_file << "\n";
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        data_column.push_back(line);
    }
    infile.close();

    // Ask the user if they want to try the vanilla search
    char choice;
    std::cout << "Do you want to try the vanilla (unencoded) search? (y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        // Create VanillaSearch object with raw data
        VanillaSearch vanilla_search(data_column);

        // Exact match query in vanilla search
        std::string exact_item;
        std::cout << "Enter the item for an exact match query: ";
        std::cin >> exact_item;

        std::vector<size_t> exact_match_indices = vanilla_search.exactMatchQuery(exact_item);

        if (!exact_match_indices.empty()) {
            std::cout << "Item found at indices: ";
            for (size_t idx : exact_match_indices) {
                std::cout << idx << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "Item not found in the column.\n";
        }

        // Prefix match query in vanilla search
        std::string prefix;
        std::cout << "Enter the prefix for a prefix match query: ";
        std::cin >> prefix;

        std::vector<size_t> prefix_match_indices = vanilla_search.prefixMatchQuery(prefix);

        if (!prefix_match_indices.empty()) {
            std::cout << "Matching items at indices: ";
            for (size_t idx : prefix_match_indices) {
                std::cout << idx << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "No items with the specified prefix found in the column.\n";
        }
    }

    // Ask the user to specify the number of threads for dictionary encoding
    int num_threads;
    std::cout << "Enter the number of threads to use for dictionary encoding: ";
    std::cin >> num_threads;

    if (num_threads <= 0) {
        std::cerr << "Number of threads must be positive.\n";
        return 1;
    }

    // Proceed with dictionary encoding
    std::cout << "Starting dictionary encoding with " << num_threads << " threads...\n";

    std::unordered_map<std::string, int> dictionary;
    std::vector<int> encoded_data;
    dictionary_encode(input_file, encoded_output_file, encoding_results_file, num_threads, dictionary, encoded_data);

    // Create QueryHandler with encoded data and dictionary
    QueryHandler query_handler(dictionary, encoded_data);

    // Exact match query in encoded data
    std::string exact_item;
    std::cout << "Enter the item for an exact match query in the encoded data: ";
    std::cin >> exact_item;

    std::vector<size_t> exact_match_indices = query_handler.exactMatchQuery(exact_item);

    if (!exact_match_indices.empty()) {
        std::cout << "Item found at indices: ";
        for (size_t idx : exact_match_indices) {
            std::cout << idx << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "Item not found in the encoded column.\n";
    }

    // Prefix match query in encoded data
    std::string prefix;
    std::cout << "Enter the prefix for a prefix match query in the encoded data: ";
    std::cin >> prefix;

    std::vector<size_t> prefix_match_indices = query_handler.prefixMatchQuery(prefix);

    if (!prefix_match_indices.empty()) {
        std::cout << "Matching items at indices: ";
        for (size_t idx : prefix_match_indices) {
            std::cout << idx << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No items with the specified prefix found in the encoded column.\n";
    }

    return 0;
}
