CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

# Все .cpp файлы (в текущей папке и в code/)
SRCS = $(wildcard *.cpp) $(shell find code -name "*.cpp")

# Папки с заголовками
INCLUDES = -I. $(addprefix -I, $(shell find code -type d))

# Исполняемый файл (в bin/ на уровень выше)
TARGET = ../bin/program

all:
	mkdir -p ../bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

run: all
	../$(TARGET)

clean:
	rm -rf ../bin

.PHONY: all run clean
