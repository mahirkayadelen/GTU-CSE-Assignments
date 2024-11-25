all: driver1_all driver2_all
driver1_all: clean clear driver1
driver2_all: clean clear driver2
driver2:
	@ javac driver2.java
	@ java driver2
driver1:
	@javac driver1.java
	@ java driver1
clean:
	rm -f *.class

clear:
	clear