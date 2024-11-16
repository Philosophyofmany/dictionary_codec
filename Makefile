# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread -march=native -msse4.2  # Added SIMD flags

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Files
SRC_FILES = $(SRC_DIR)/main.cpp \
            $(SRC_DIR)/encoding/dictionary_encoder.cpp \
            $(SRC_DIR)/encoding/multi_threading.cpp \
            $(SRC_DIR)/query/query_handler.cpp \
            $(SRC_DIR)/query/query_utils.cpp \
            $(SRC_DIR)/query/vanilla_search.cpp \
            $(SRC_DIR)/performance/performance_test.cpp  # Corrected path

OBJ_FILES = $(OBJ_DIR)/main.o \
            $(OBJ_DIR)/dictionary_encoder.o \
            $(OBJ_DIR)/multi_threading.o \
            $(OBJ_DIR)/query_handler.o \
            $(OBJ_DIR)/query_utils.o \
            $(OBJ_DIR)/vanilla_search.o \
            $(OBJ_DIR)/performance_test.o  # Corrected path

# Targets
all: $(BIN_DIR)/dictionary_encoder

# Compile .cpp files to .o
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/dictionary_encoder.o: $(SRC_DIR)/encoding/dictionary_encoder.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/multi_threading.o: $(SRC_DIR)/encoding/multi_threading.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/query_handler.o: $(SRC_DIR)/query/query_handler.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/query_utils.o: $(SRC_DIR)/query/query_utils.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/vanilla_search.o: $(SRC_DIR)/query/vanilla_search.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/performance_test.o: $(SRC_DIR)/performance/performance_test.cpp  # Added rule for performance_test.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Link object files into executable
$(BIN_DIR)/dictionary_encoder: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean object and binary files
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/dictionary_encoder
