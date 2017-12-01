PROGS=main1 main2
include ../../XX/Makefile.rules


test1: main1 ../test1.txt
	@echo "expected results: 3, 4, 0, 9"
	@./main1 < ../test1.txt

puzzle1: main1 ../puzzle1.txt
	@echo "puzzle result:"
	@./main1 < ../puzzle1.txt


test2: main2 ../test2.txt
	@echo "expected results: 6, 0, 4, 12, 4"
	@./main2 < ../test2.txt

puzzle2: main2 ../puzzle1.txt
	@echo "puzzle result:"
	@./main2 < ../puzzle1.txt
