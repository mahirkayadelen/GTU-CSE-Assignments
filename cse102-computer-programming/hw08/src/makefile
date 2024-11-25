all : clean compile run

compile: main.c util.c util.h
	@echo "COMPILING......."
	@gcc main.c util.c -o test
run:
	@echo "Running the tests..."
	./test
clean:
	@echo "---------------------"
	@echo "Removing compiled files"
	@rm -f *.o
	@rm -f test
