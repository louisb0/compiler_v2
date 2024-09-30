CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -MMD -MP
INCLUDES = -I./src

SRC_DIR = src
BUILD_DIR = build

SRCS = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

TARGET = compile

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) $(BUILD_DIR)/$(SRC_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)

.PHONY: all clean
