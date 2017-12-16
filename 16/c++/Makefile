include ../../XX/Makefile.rules


test1: part1
	@echo "expected: baedc"
	@time ./$< abcde < ../test1.txt

puzzle1: part1
	@echo "puzzle result:"
	@time ./$< abcdefghijklmnop < ../puzzle1.txt

puzzle2: part2
	@echo "puzzle result:"
	@time ./$< abcdefghijklmnop < ../puzzle1.txt
