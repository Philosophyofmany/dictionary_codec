# Dictionary Encoder

This project provides a dictionary encoding and querying system with performance testing capabilities. The program allows you to encode data using multiple threads, test performance with different configurations, and query the dictionary using exact match or prefix search, with and without SIMD optimization.

## Prerequisites

Before running the program, ensure that you have the necessary build tools and dependencies. This project uses `Makefile` to build the code.

## Installation

1. Clone the repository:

   ```bash
   git clone <repository-url>
   cd <project-directory>
   ```

2. Build the project by running:

   ```bash
   make
   ```

## Running the Program

After building the project, you can execute the dictionary encoder by running:

```bash
./bin/dictionary_encoder
```

### Program Flow

Upon execution, you will be prompted with a series of options:

1. **Performance Test**: The program will ask if you want to run a performance test. If you choose "Yes", the test will perform an encoding process with different numbers of threads and display the results. The performance test will also run a query test, which includes:
   - Exact match search
   - Prefix search
   - Tests with and without SIMD optimizations
   These results will be saved to the `results/encoding_results.txt`, `results/performance_results.txt`, and `results/query_results.txt` files.

2. **Vanilla Search**: If you decline the performance test, you will be prompted to use a basic search feature, called "vanilla search", which doesn't use any encoding or performance optimizations. You can enter:
   - **Prefix search**
   - **Exact match search**
   This is a non-optimized query method.

3. **Dictionary Encoding**: After the test, the program will ask how many threads to use for encoding the dictionary. The dictionary will be encoded based on the specified number of threads. The terminal will then provide the location of the encoded files if you'd like to view them.

4. **SIMD Optimization**: Once encoding is complete, the program will ask if you'd like to query using SIMD optimizations. If you choose "Yes", you will be prompted with the same exact match or prefix query options, but with SIMD optimization enabled. If you select "No", the program will revert to querying without SIMD optimizations.

### Results

- **Encoding Results**: Saved to `results/encoding_results.txt`
- **Performance Results**: Saved to `results/performance_results.txt`
- **Query Results**: Saved to `results/query_results.txt`

These files will contain the timings and details of the tests performed.
