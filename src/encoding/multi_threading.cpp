#include "../../include/multi_threading.h"
#include <thread>
#include <mutex>

std::mutex dict_mutex;

// Global mutex for thread-safe operations
extern std::mutex dict_mutex;

// Function to process data chunks for multi-threaded dictionary encoding
void process_data_chunk(const std::vector<std::string>& data, std::unordered_map<std::string, int>& dictionary, int start_idx, int end_idx) {
    std::unordered_map<std::string, int> local_dict;
    for (int i = start_idx; i < end_idx; ++i) {
        local_dict[data[i]] = 0; // Add unique item to the local dictionary
    }

    // Lock the global dictionary and merge the local dictionary
    {
        std::lock_guard<std::mutex> lock(dict_mutex);
        for (auto& item : local_dict) {
            if (dictionary.find(item.first) == dictionary.end()) {
                dictionary[item.first] = dictionary.size(); // Assign a new ID
            }
        }
    }
}

// Function to handle dictionary encoding with multi-threading
void dictionary_encode_multi_threaded(const std::vector<std::string>& data, std::unordered_map<std::string, int>& dictionary, int num_threads) {
    int chunk_size = data.size() / num_threads;
    std::vector<std::thread> threads;

    // Create threads to process chunks
    for (int i = 0; i < num_threads; ++i) {
        int start_idx = i * chunk_size;
        int end_idx = (i == num_threads - 1) ? data.size() : (i + 1) * chunk_size;
        threads.emplace_back(process_data_chunk, std::cref(data), std::ref(dictionary), start_idx, end_idx);
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }
}
