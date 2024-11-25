all : clean compile run

compile: main.c utils.c utils.h
	@echo "COMPILING......."
	@gcc main.c utils.c -o test
run:
	@echo "Running the tests..."
	./test
clean:
	@echo "---------------------"
	@echo "Removing compiled files"
	@rm -f *.o
	@rm -f test
	@rm -f customeraccount.txt
