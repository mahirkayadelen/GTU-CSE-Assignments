all: clean compile run

compile: main.cpp hw1.cpp tetro.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -o test main.cpp hw1.cpp

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./test
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f test