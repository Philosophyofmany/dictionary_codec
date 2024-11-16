#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include "../../include/dictionary_encoder.h"
#include "../../include/query_handler.h"
#include "../../include/vanilla_search.h"

void test_performance(const std::string& input_file, const std::string& output_file) {
    std::ofstream performance_file(output_file);
    if (!performance_file.is_open()) {
        std::cerr << "Error opening file: " << output_file << std::endl;
        return;
    }

    // Write header for encoding and query performance results
    performance_file << "Phase,Query Type,Search Type,Time (ms)\n";

    std::vector<int> thread_numbers = {1, 2, 4, 8, 16}; // Number of threads to test
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> encoded_data;

    // Load raw data for vanilla search
    std::vector<std::string> data_column;
    std::ifstream infile(input_file);
    if (!infile.is_open()) {
        std::cerr << "Error opening input file: " << input_file << "\n";
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        data_column.push_back(line);
    }
    infile.close();

    // Create VanillaSearch object with raw data
    VanillaSearch vanilla_search(data_column);

    // Encoding phase
    std::cout << "Starting Encoding Phase..." << std::endl;
    for (int num_threads : thread_numbers) {
        auto start_time = std::chrono::high_resolution_clock::now();
        dictionary_encode(input_file, "temp_encoded.txt", "temp_results.txt", num_threads, dictionary, encoded_data);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        performance_file << "Encoding,NA,NA," << duration << "\n";
        std::cout << "Encoding, Threads: " << num_threads << ", Time: " << duration << " ms\n";
    }

    // Create QueryHandler with encoded data and dictionary
    QueryHandler query_handler(dictionary, encoded_data);

    // Query phase
    std::cout << "\nStarting Query Phase..." << std::endl;

    // Test Exact Match Queries with SIMD and without SIMD
    {
        std::string exact_item = "gjcznimfn"; // Use a default item for testing

        // Non-SIMD (Vanilla search for exact match)
        auto start_time = std::chrono::high_resolution_clock::now();
        vanilla_search.exactMatchQuery(exact_item); // Non-SIMD search
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        performance_file << "Exact Match,Non-SIMD," << duration << "\n";
        std::cout << "Exact Match (Non-SIMD), Time: " << duration << " ms\n";

        // SIMD (QueryHandler for exact match)
        start_time = std::chrono::high_resolution_clock::now();
        query_handler.exactMatchQuery(exact_item); // SIMD search
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        performance_file << "Exact Match,SIMD," << duration << "\n";
        std::cout << "Exact Match (SIMD), Time: " << duration << " ms\n";
    }

    // Test Prefix Match Queries with SIMD and without SIMD
    {
        std::string prefix = "de"; // Use a default prefix for testing

        // Non-SIMD (Vanilla search for prefix match)
        auto start_time = std::chrono::high_resolution_clock::now();
        vanilla_search.prefixMatchQuery(prefix); // Non-SIMD search
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        performance_file << "Prefix Match,Non-SIMD," << duration << "\n";
        std::cout << "Prefix Match (Non-SIMD), Time: " << duration << " ms\n";

        // SIMD (QueryHandler for prefix match)
        start_time = std::chrono::high_resolution_clock::now();
        query_handler.prefixMatchQuery(prefix); // SIMD search
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        performance_file << "Prefix Match,SIMD," << duration << "\n";
        std::cout << "Prefix Match (SIMD), Time: " << duration << " ms\n";
    }

    performance_file.close();
    std::cout << "\nQuery performance results saved to " << output_file << std::endl;
}
