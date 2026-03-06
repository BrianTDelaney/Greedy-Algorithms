CXX = g++
CXXFLAGS = -Wall -std=c++17

main: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o main

clean:
	rm -f main