#include "../../include/vanilla_search.h"
#include <chrono>
#include <iostream>

VanillaSearch::VanillaSearch(const std::vector<std::string>& data_column)
    : data_column_(data_column) {}

// Exact match query: finds all occurrences of the data item in the unencoded column
std::vector<size_t> VanillaSearch::exactMatchQuery(const std::string& data_item) const {
    std::vector<size_t> indices;

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < data_column_.size(); ++i) {
        if (data_column_[i] == data_item) {
            indices.push_back(i);
        }
    }

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Exact match query took " << duration << " µs.\n";

    return indices;
}

// Prefix match query: finds all items that start with the specified prefix in the unencoded column
std::vector<size_t> VanillaSearch::prefixMatchQuery(const std::string& prefix) const {
    std::vector<size_t> indices;

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < data_column_.size(); ++i) {
        if (data_column_[i].rfind(prefix, 0) == 0) {  // Checks if prefix matches from the start
            indices.push_back(i);
        }
    }

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Prefix match query took " << duration << " µs.\n";

    return indices;
}
