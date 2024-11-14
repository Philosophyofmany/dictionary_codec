#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <chrono>  // Added for timing
#include "../include/dictionary_encoder.h"
#include "../include/query_handler.h"
#include "../include/vanilla_search.h"  // Include VanillaSearch header

int main() {
    // Define paths for input, output, and result files
    std::string input_file = "data/Column.txt";  // Raw data file path
    std::string encoded_output_file = "data/encoded_column.txt";  // Encoded output data path
    std::string encoding_results_file = "results/encoding_results.txt";  // Dictionary encoding result path
    int num_threads = 4;  // Number of threads to use for multi-threading

    // Load raw data for vanilla search
    std::vector<std::string> data_column;
    std::ifstream infile(input_file);
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

        // Start timing vanilla search exact match
        auto start_vanilla_exact = std::chrono::high_resolution_clock::now();
        std::vector<size_t> exact_match_indices = vanilla_search.exactMatchQuery(exact_item);
        auto end_vanilla_exact = std::chrono::high_resolution_clock::now();
        auto vanilla_exact_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_vanilla_exact - start_vanilla_exact);

        if (!exact_match_indices.empty()) {
            std::cout << "Item found at indices: ";
            for (size_t idx : exact_match_indices) {
                std::cout << idx << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "Item not found in the column.\n";
        }
        std::cout << "Vanilla search (exact match) took " << vanilla_exact_duration.count() << " ms.\n";

        // Prefix match query in vanilla search
        std::string prefix;
        std::cout << "Enter the prefix for a prefix match query: ";
        std::cin >> prefix;

        // Start timing vanilla search prefix match
        auto start_vanilla_prefix = std::chrono::high_resolution_clock::now();
        std::vector<size_t> prefix_match_indices = vanilla_search.prefixMatchQuery(prefix);
        auto end_vanilla_prefix = std::chrono::high_resolution_clock::now();
        auto vanilla_prefix_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_vanilla_prefix - start_vanilla_prefix);

        if (!prefix_match_indices.empty()) {
            std::cout << "Matching items at indices: ";
            for (size_t idx : prefix_match_indices) {
                std::cout << idx << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "No items with the specified prefix found in the column.\n";
        }
        std::cout << "Vanilla search (prefix match) took " << vanilla_prefix_duration.count() << " ms.\n";
    }

    // Proceed with dictionary encoding
    std::cout << "Starting dictionary encoding...\n";

    // Start timing dictionary encoding
    auto start_encoding = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> encoded_data;
    dictionary_encode(input_file, encoded_output_file, encoding_results_file, num_threads, dictionary, encoded_data);
    auto end_encoding = std::chrono::high_resolution_clock::now();
    auto encoding_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_encoding - start_encoding);

    std::cout << "Dictionary encoding took " << encoding_duration.count() << " ms.\n";
    std::cout << "Dictionary after encoding:\n";
    for (const auto& entry : dictionary) {
        std::cout << entry.first << " -> " << entry.second << "\n";
    }

    std::cout << "Encoded data (IDs): ";
    for (const int encoded_value : encoded_data) {
        std::cout << encoded_value << " ";
    }
    std::cout << "\n";

    // Create QueryHandler with encoded data and dictionary
    QueryHandler query_handler(dictionary, encoded_data);

    // Exact match query in encoded data
    std::string exact_item;
    std::cout << "Enter the item for an exact match query in the encoded data: ";
    std::cin >> exact_item;

    // Start timing encoded data exact match
    auto start_encoded_exact = std::chrono::high_resolution_clock::now();
    std::vector<size_t> exact_match_indices = query_handler.exactMatchQuery(exact_item);
    auto end_encoded_exact = std::chrono::high_resolution_clock::now();
    auto encoded_exact_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_encoded_exact - start_encoded_exact);

    if (!exact_match_indices.empty()) {
        std::cout << "Item found at indices: ";
        for (size_t idx : exact_match_indices) {
            std::cout << idx << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "Item not found in the encoded column.\n";
    }
    std::cout << "Encoded search (exact match) took " << encoded_exact_duration.count() << " ms.\n";

    // Prefix match query in encoded data
    std::string prefix;
    std::cout << "Enter the prefix for a prefix match query in the encoded data: ";
    std::cin >> prefix;

    // Start timing encoded data prefix match
    auto start_encoded_prefix = std::chrono::high_resolution_clock::now();
    std::vector<size_t> prefix_match_indices = query_handler.prefixMatchQuery(prefix);
    auto end_encoded_prefix = std::chrono::high_resolution_clock::now();
    auto encoded_prefix_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_encoded_prefix - start_encoded_prefix);

    if (!prefix_match_indices.empty()) {
        std::cout << "Matching items at indices: ";
        for (size_t idx : prefix_match_indices) {
            std::cout << idx << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No items with the specified prefix found in the encoded column.\n";
    }
    std::cout << "Encoded search (prefix match) took " << encoded_prefix_duration.count() << " ms.\n";

    return 0;
}
