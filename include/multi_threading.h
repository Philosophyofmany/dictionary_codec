#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H
#include <mutex>

#include <vector>
#include <string>
#include <unordered_map>

// Multi-threaded function for dictionary encoding
void process_data_chunk(const std::vector<std::string>& data, std::unordered_map<std::string, int>& dictionary, int start_idx, int end_idx);

// Function to handle dictionary encoding with multi-threading
void dictionary_encode_multi_threaded(const std::vector<std::string>& data, std::unordered_map<std::string, int>& dictionary, int num_threads);

#endif // MULTI_THREADING_H
