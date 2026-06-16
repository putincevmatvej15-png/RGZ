CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

# Все .cpp файлы
SRCS = $(wildcard *.cpp) $(shell find code -name "*.cpp")

# Все папки с заголовками
INCLUDES = -I. $(addprefix -I, $(shell find code -type d))

# Исполняемый файл
TARGET = ../bin/program

all:
	mkdir -p ../bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

run: all
	$(TARGET)

clean:
	rm -rf ../bin

.PHONY: all run clean
