all: driverone runone clean1 drivertwo runtwo clean2

driverone: hw1_1.c
	@echo "-------------------------------------------"
	@echo Compiling first question
	@gcc -o appendMeMore hw1_1.c
runone:
	@echo "running the appendMeMore without x argument and with x argument"
	@echo "================================================================================="
	./appendMeMore f1 1000000 & ./appendMeMore f1 1000000
	./appendMeMore f2 1000000 x & ./appendMeMore f2 1000000 x

	@echo "================================================================================="
	@echo "Completed test1..."

clean1: 
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f appendMeMore
	@rm -f *.o
	
drivertwo: hw1_2.c
	@echo "-------------------------------------------"
	@echo Compiling second driver...
	@gcc -o test2  hw1_2.c
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