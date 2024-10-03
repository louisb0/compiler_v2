CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -MMD -MP
INCLUDES = -I./src

SRC_DIR = src
BUILD_DIR = build

SRCS = main.cpp $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/visitors/*.cpp)
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

TARGET = bin

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) $(BUILD_DIR)/$(SRC_DIR) $(BUILD_DIR)/$(SRC_DIR)/visitors

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)

.PHONY: all clean
