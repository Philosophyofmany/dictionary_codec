#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include "../../include/dictionary_encoder.h"
#include "../../include/performance_test.h"

void test_performance(const std::string& input_file, const std::string& output_file) {
    std::ofstream performance_file(output_file);
    if (!performance_file.is_open()) {
        std::cerr << "Error opening file: " << output_file << std::endl;
        return;
    }

    // Write header for performance comparison results
    performance_file << "Threads,Time (ms)\n";

    std::vector<int> thread_numbers = {1, 2, 4, 8, 16}; // Number of threads to test
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> encoded_data;

    // Loop through different thread numbers
    for (int num_threads : thread_numbers) {
        dictionary.clear();
        encoded_data.clear();

        // Measure the encoding time
        auto start_time = std::chrono::high_resolution_clock::now();
        dictionary_encode(input_file, "temp_encoded.txt", "temp_results.txt", num_threads, dictionary, encoded_data);
        auto end_time = std::chrono::high_resolution_clock::now();

        // Calculate the duration in milliseconds
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

        // Log the result
        performance_file << num_threads << "," << duration << "\n";
        std::cout << "Threads: " << num_threads << ", Time: " << duration << " ms\n";
    }

    performance_file.close();
    std::cout << "Performance results saved to " << output_file << std::endl;
}
