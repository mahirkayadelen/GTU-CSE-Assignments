all : clean clear compile  run 


compile : driver2.o
	@g++ driver2.o -lm -o driver2.out
	
driver2.o :
	@g++ -g -std=c++11 -c driver2.cpp -o driver2.o
	
run :
	@./driver2.out
	
	
clean :
	@rm -f *.out
	@rm -f *.o

clear : 
	@clear

