CXXFLAGS=-std=c++11 -O3 -W -Wall

part1: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

test: part1
	@echo "Expected: 3 0 2 3"
	@./$< < ../test1.txt

puzzle: part1
	@./$< < ../puzzle1.txt
