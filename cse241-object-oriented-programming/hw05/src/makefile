all: driverone runone clean1 drivertwo runtwo clean2

driverone: driver.cpp hw1.cpp TetrisAdapter.cpp TetrisArray1D.cpp TetrisVector.cpp
	@echo "-------------------------------------------"
	@echo Compiling firs driver...
	@g++ -std=c++11 -o test1 driver.cpp hw1.cpp TetrisAdapter.cpp TetrisArray1D.cpp TetrisVector.cpp
runone:
	@echo "running the test1"
	@echo "================================================================================="
	./test1
	@echo "================================================================================="
	@echo "Completed test1..."

clean1: 
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f test1
	
drivertwo: driver2.cpp hw1.cpp TetrisAdapter.cpp TetrisArray1D.cpp TetrisVector.cpp
	@echo "-------------------------------------------"
	@echo Compiling second driver...
	@g++ -std=c++11 -o test2 driver2.cpp hw1.cpp TetrisAdapter.cpp TetrisArray1D.cpp TetrisVector.cpp
runtwo:
	@echo "running the test2"
	@echo "================================================================================="
	./test2
	@echo "================================================================================="
	@echo "Completed test2..."

clean2: 
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f test2