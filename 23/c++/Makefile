include ../../XX/Makefile.rules


test1: part1
	@echo "expected: 4"
	@time ./$< < ../test1.txt

puzzle1: part1
	@echo "puzzle result:"
	@time ./$< < ../puzzle1.txt

puzzle2:
	$(CXX) $(CXXFLAGS) -o part2 main2.cpp
	./part2 
