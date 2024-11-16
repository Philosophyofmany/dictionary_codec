#include "../../include/query_utils.h"
#include <immintrin.h> // For SIMD instructions on x86 (AVX2)

namespace QueryUtils {

// Checks if a string starts with the given prefix using AVX2 instructions
bool startsWithSIMD(const std::string& str, const std::string& prefix) {
    size_t prefix_len = prefix.length();
    if (str.length() < prefix_len) return false;

    size_t i = 0;

    // Compare in chunks of 32 bytes (256 bits) using AVX2
    for (; i + 32 <= prefix_len; i += 32) {
        // Load 32 bytes (256 bits) from both the string and the prefix
        __m256i str_chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(str.data() + i));
        __m256i prefix_chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(prefix.data() + i));

        // Compare 32 characters (256 bits) at once
        __m256i cmp_result = _mm256_cmpeq_epi8(str_chunk, prefix_chunk);

        // Check if all characters match
        if (_mm256_testc_si256(cmp_result, cmp_result) == 0) {
            return false; // If any mismatch, return false
        }
    }

    // Handle any remaining characters that were not part of a full 32-byte chunk
    for (; i < prefix_len; ++i) {
        if (str[i] != prefix[i]) return false;
    }

    return true;
}

// Exact Match Search using AVX2 instructions
bool exactMatchSIMD(const std::string& str, const std::string& target) {
    size_t target_len = target.length();
    if (str.length() != target_len) return false;  // Early exit if lengths don't match

    size_t i = 0;

    // Compare in chunks of 32 bytes (256 bits) using AVX2
    for (; i + 32 <= target_len; i += 32) {
        // Load 32 bytes (256 bits) from both the string and the target
        __m256i str_chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(str.data() + i));
        __m256i target_chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(target.data() + i));

        // Compare 32 characters (256 bits) at once
        __m256i cmp_result = _mm256_cmpeq_epi8(str_chunk, target_chunk);

        // If any byte in the chunk doesn't match, return false
        if (_mm256_testc_si256(cmp_result, cmp_result) == 0) {
            return false;
        }
    }

    // Handle any remaining characters that were not part of a full 32-byte chunk
    for (; i < target_len; ++i) {
        if (str[i] != target[i]) return false;
    }

    return true;
}

} // namespace QueryUtils
