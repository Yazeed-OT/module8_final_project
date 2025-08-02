# Final Project - Professional Makefile
# Author: Yazeed Alotaibi
# Course: CSCI 201 – Computer Science II

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -std=c++17 -Iinclude

# Directories
BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
INCLUDE_DIR = include

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLE = $(BIN_DIR)/BankingSystem

# Colors
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

# Default target
all: $(BIN_DIR) $(OBJ_DIR) $(EXECUTABLE)

# Ensure bin and obj directories exist
$(BIN_DIR) $(OBJ_DIR):
	@echo "$(BLUE)[INFO]$(RESET) Creating directory $@"
	@mkdir -p $@

# Link object files into the final executable
$(EXECUTABLE): $(OBJECTS)
	@echo "$(GREEN)[LINK]$(RESET) Linking -> $@"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ -lstdc++fs

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "$(YELLOW)[COMPILING]$(RESET) $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: all
	@echo "$(GREEN)[RUN]$(RESET) Executing -> ./$(EXECUTABLE)"
	@./$(EXECUTABLE)

# Clean build files
clean:
	@echo "[CLEAN] Removing build files and generated data..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)/BankingSystem BankingSystem
	rm -f bank_data.txt financial_report.txt

# Rebuild the project from scratch
rebuild: clean all

# Mark targets as phony
.PHONY: all clean run rebuild
