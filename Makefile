CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

SRC_DIR = src
CODE_DIR = src/code

# Все .cpp файлы
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(shell find $(CODE_DIR) -name "*.cpp")

# Автоматически найти все папки с заголовками
INCLUDE_DIRS = $(shell find $(CODE_DIR) -type d)
INCLUDES = $(addprefix -I,$(INCLUDE_DIRS)) -I$(SRC_DIR)

TARGET = bin/program

all:
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf bin

.PHONY: all run clean
