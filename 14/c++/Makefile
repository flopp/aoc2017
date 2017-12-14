CXXFLAGS=-std=c++11 -O3 -W -Wall

part1: main1.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

part2: main2.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


test1: part1
	@echo "expected: 8108, 1242"
	@./$< < ../test1.txt

puzzle1: part1
	@./$< < ../puzzle1.txt

