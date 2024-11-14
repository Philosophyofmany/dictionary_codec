#include "../../include/query_utils.h"
#include <immintrin.h> // For SIMD instructions on x86

namespace QueryUtils {

// Checks if a string starts with the given prefix using SIMD instructions
bool startsWithSIMD(const std::string& str, const std::string& prefix) {
    size_t prefix_len = prefix.length();
    if (str.length() < prefix_len) return false;

    size_t i = 0;
    for (; i + 16 <= prefix_len; i += 16) {
        __m128i str_chunk = _mm_loadu_si128(reinterpret_cast<const __m128i*>(str.data() + i));
        __m128i prefix_chunk = _mm_loadu_si128(reinterpret_cast<const __m128i*>(prefix.data() + i));

        // Compare 16 characters at once
        int result = _mm_cmpestri(str_chunk, 16, prefix_chunk, 16, _SIDD_CMP_EQUAL_EACH);
        if (result != 0) return false; // If not equal, return false
    }

    // Compare remaining characters
    for (; i < prefix_len; ++i) {
        if (str[i] != prefix[i]) return false;
    }
    return true;
}

}
