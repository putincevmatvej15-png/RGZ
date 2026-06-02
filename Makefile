CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: crypto

crypto: main.o vernam.o trithemius.o
	$(CXX) $(CXXFLAGS) -o crypto main.o vernam.o trithemius.o

main.o: main.cpp cipher_helper.h
	$(CXX) $(CXXFLAGS) -c main.cpp

vernam.o: vernam.cpp vernam.h cipher_helper.h
	$(CXX) $(CXXFLAGS) -c vernam.cpp

trithemius.o: trithemius.cpp trithemius.h cipher_helper.h
	$(CXX) $(CXXFLAGS) -c trithemius.cpp

clean:
	rm -f *.o crypto

run: crypto
	./crypto