SRC_DIR := src
BIN_DIR := bin

SRC := $(wildcard $(SRC_DIR)/*.cpp)
INC := $(foreach dir, $(shell find include -type d),-I $(dir))

CXX = g++-13
CXXFLAGS = -Wall -O2 -std=c++2b $(INC)

all: $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRC))

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp	
	$(CXX) $(CXXFLAGS) $< -o $@
