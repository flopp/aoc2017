CXXFLAGS=-std=c++11 -O3 -W -Wall

part1: main1.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

part2: main2.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


test1: part1
	@./$< 5 < ../test1.txt

puzzle1: part1
	@./$< 256 < ../puzzle1.txt

test2: part2
	@echo -n ""         | ./$< ; echo
	@echo -n "AoC 2017" | ./$< ; echo
	@echo -n "1,2,3"    | ./$< ; echo
	@echo -n "1,2,4"    | ./$< ; echo

puzzle2: part2
	@./$< < ../puzzle1.txt
