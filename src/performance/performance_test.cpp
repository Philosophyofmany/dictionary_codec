#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <iomanip>
#include "../../include/dictionary_encoder.h"
#include "../../include/query_handler.h"

// Function to test encoding and query performance
void test_performance(const std::string& input_file, const std::string& output_file) {
    // Encoding Test
    std::ofstream performance_file(output_file);
    if (!performance_file.is_open()) {
        std::cerr << "Error opening file: " << output_file << std::endl;
        return;
    }

    performance_file << "Encoding Tests\n";
    performance_file << "Threads  | Time (ms)\n";
    performance_file << "------------------------\n"; // separator

    std::vector<int> thread_numbers = {1, 2, 4, 8, 16, 20}; // Number of threads to test
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> encoded_data;

    // Load raw data
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

    // Perform encoding tests
    for (int num_threads : thread_numbers) {
        dictionary.clear();
        encoded_data.clear();

        auto start_time = std::chrono::high_resolution_clock::now();

        // Perform encoding with the given thread count
        dictionary_encode(input_file, "temp_encoded.txt", "temp_results.txt", num_threads, dictionary, encoded_data);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

        performance_file << std::setw(6) << num_threads << " | " << std::setw(10) << duration << "\n";
        std::cout << "Encoding, Threads: " << num_threads << ", Time: " << duration << " ms\n";
    }

    performance_file.close();
    std::cout << "Encoding performance results saved to " << output_file << std::endl;

    // Step 2: Query Test
    // Add exact match terms
    std::vector<std::string> exact_match_queries = {
        "uyadc", "ikjsyqehs", "yafcyuc", "odbeyulzt", "wzmbpd",
        "edwdyswjf", "vbtjs", "mzsirlq", "qwlarkmbw"
    };

    // Add prefix match terms (using the first 3 characters for each)
    std::vector<std::string> prefix_match_queries = {
        "uya", "ikj", "yaf", "odb", "wzm",
        "edw", "vbt", "mzs", "qwl"
    };

    // Assuming dictionary and encoded_data are already populated from the encoding phase
    // Create a QueryHandler object using the dictionary and encoded data
    QueryHandler query_handler(dictionary, encoded_data);

    // Open a file to save query results in the "results" directory
    std::ofstream query_results_file("results/query_results.txt");
    if (!query_results_file.is_open()) {
        std::cerr << "Error opening query results file.\n";
        return;
    }

    query_results_file << "Query Tests Results\n";
    query_results_file << "Query Type | Query Term | Indices | Time (µs)\n";
    query_results_file << "--------------------------------------------\n"; // separator

    std::cout << "Running query tests...\n";
    std::cout << "Testing default queries: \"psud\" (exact match) and \"ps\" (prefix match)\n";

    std::unordered_map<std::string, long> query_durations; // Save durations of previous queries

    // Exact match query tests (SIMD version)
    for (const std::string& exact_item : exact_match_queries) {
        std::vector<size_t> exact_match_indices = query_handler.exactMatchQuery(exact_item);
        query_durations["exact_" + exact_item] = query_handler.getLastQueryDuration(); // Retrieve last query duration

        query_results_file << "Exact Match | " << exact_item << " | ";
        if (!exact_match_indices.empty()) {
            for (size_t idx : exact_match_indices) {
                query_results_file << idx << " ";
            }
        } else {
            query_results_file << "No match found";
        }
        query_results_file << " | Time: " << query_durations["exact_" + exact_item] << " µs\n";
    }

    // Exact match query tests (No SIMD version)
    for (const std::string& exact_item : exact_match_queries) {
        std::vector<size_t> exact_match_indices_no_simd = query_handler.exactMatchQueryNoSIMD(exact_item);
        query_durations["exact_no_simd_" + exact_item] = query_handler.getLastQueryDuration(); // Retrieve last query duration

        query_results_file << "Exact Match No SIMD | " << exact_item << " | ";
        if (!exact_match_indices_no_simd.empty()) {
            for (size_t idx : exact_match_indices_no_simd) {
                query_results_file << idx << " ";
            }
        } else {
            query_results_file << "No match found";
        }
        query_results_file << " | Time: " << query_durations["exact_no_simd_" + exact_item] << " µs\n";
    }

    // Prefix match query tests (SIMD version)
    for (const std::string& prefix : prefix_match_queries) {
        std::vector<size_t> prefix_match_indices = query_handler.prefixMatchQuery(prefix);
        query_durations["prefix_" + prefix] = query_handler.getLastQueryDuration(); // Retrieve last query duration

        query_results_file << "Prefix Match | " << prefix << " | ";
        if (!prefix_match_indices.empty()) {
            for (size_t idx : prefix_match_indices) {
                query_results_file << idx << " ";
            }
        } else {
            query_results_file << "No match found";
        }
        query_results_file << " | Time: " << query_durations["prefix_" + prefix] << " µs\n";
    }

    // Prefix match query tests (No SIMD version)
    for (const std::string& prefix : prefix_match_queries) {
        std::vector<size_t> prefix_match_indices_no_simd = query_handler.prefixMatchQueryNoSIMD(prefix);
        query_durations["prefix_no_simd_" + prefix] = query_handler.getLastQueryDuration(); // Retrieve last query duration

        query_results_file << "Prefix Match No SIMD | " << prefix << " | ";
        if (!prefix_match_indices_no_simd.empty()) {
            for (size_t idx : prefix_match_indices_no_simd) {
                query_results_file << idx << " ";
            }
        } else {
            query_results_file << "No match found";
        }
        query_results_file << " | Time: " << query_durations["prefix_no_simd_" + prefix] << " µs\n";
    }

    query_results_file.close();
    std::cout << "Query results saved to results/query_results.txt\n";
}
