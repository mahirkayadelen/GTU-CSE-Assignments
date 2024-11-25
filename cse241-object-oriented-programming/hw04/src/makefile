all: clean compile run 

compile: main.cpp DayOfYearSet.cpp DayOfYearSet.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -o test main.cpp DayOfYearSet.cpp

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