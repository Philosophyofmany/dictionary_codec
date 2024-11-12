# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files and object files
SRC_FILES = $(SRC_DIR)/main.cpp \
            $(SRC_DIR)/encoding/dictionary_encoder.cpp \
            $(SRC_DIR)/encoding/multi_threading.cpp

OBJ_FILES = $(OBJ_DIR)/main.o \
            $(OBJ_DIR)/dictionary_encoder.o \
            $(OBJ_DIR)/multi_threading.o

# Executable
TARGET = $(BIN_DIR)/dictionary_encoder

# Create necessary directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Rule to build the project and run
run: $(TARGET)
	./$(TARGET) data/encoded_column.txt results/encoding_results.txt

# Compile main.o
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/dictionary_encoder.h $(INCLUDE_DIR)/multi_threading.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile dictionary_encoder.o
$(OBJ_DIR)/dictionary_encoder.o: $(SRC_DIR)/encoding/dictionary_encoder.cpp $(INCLUDE_DIR)/dictionary_encoder.h $(INCLUDE_DIR)/multi_threading.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile multi_threading.o
$(OBJ_DIR)/multi_threading.o: $(SRC_DIR)/encoding/multi_threading.cpp $(INCLUDE_DIR)/multi_threading.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJ_DIR) $(BIN_DIR) $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(TARGET)

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: run clean
