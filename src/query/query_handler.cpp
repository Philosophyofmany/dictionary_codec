#include "../../include/query_handler.h"
#include "../../include/query_utils.h"
#include <immintrin.h> // For SIMD instructions
#include <iostream>
#include <chrono> // For timing

// Constructor to initialize the dictionary, encoded data, and index map
QueryHandler::QueryHandler(const std::unordered_map<std::string, int>& dictionary, const std::vector<int>& encoded_data)
    : dictionary_(dictionary), encoded_data_(encoded_data) {
    // Build an index map for quick lookup of data item positions
    for (size_t i = 0; i < encoded_data.size(); ++i) {
        data_index_[encoded_data[i]].push_back(i);
    }
}

// Exact match query with timing
std::vector<size_t> QueryHandler::exactMatchQuery(const std::string& data_item) const {
    auto start = std::chrono::high_resolution_clock::now(); // Start timing

    std::vector<size_t> result;
    auto it = dictionary_.find(data_item);
    if (it != dictionary_.end()) {
        int encoded_value = it->second;
        if (data_index_.count(encoded_value)) {
            result = data_index_.at(encoded_value); // Get all indices of the exact match

            // Print the corresponding words for the found indices
            std::cout << "Exact Match Query for item \"" << data_item << "\":\n";
            for (size_t idx : result) {
                std::cout << "Index: " << idx << " -> Word: " << data_item << std::endl;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // End timing
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Exact Match Query took " << duration << " µs.\n";

    return result;
}

// Prefix match query with SIMD optimization and timing
std::vector<size_t> QueryHandler::prefixMatchQuery(const std::string& prefix) const {
    auto start = std::chrono::high_resolution_clock::now(); // Start timing

    std::vector<size_t> result;
    for (const auto& [data_item, encoded_value] : dictionary_) {
        if (QueryUtils::startsWithSIMD(data_item, prefix)) {
            if (data_index_.count(encoded_value)) {
                const auto& indices = data_index_.at(encoded_value);
                result.insert(result.end(), indices.begin(), indices.end());

                // Print the corresponding words for the found indices
                std::cout << "Prefix Match Query for prefix \"" << prefix << "\":\n";
                for (size_t idx : indices) {
                    std::cout << "Index: " << idx << " -> Word: " << data_item << std::endl;
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // End timing
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Prefix Match Query took " << duration << " µs.\n";

    return result;
}
