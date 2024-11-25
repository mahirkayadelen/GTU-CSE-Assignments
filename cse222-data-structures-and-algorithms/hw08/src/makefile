JAVAC = javac
JAVA = java
FLAGS = -g

SOURCES = Person.java SocialNetworkGraph.java Main.java

CLASSES = Person.class SocialNetworkGraph.class Main.class

all: run

%.class: %.java
	$(JAVAC) $(FLAGS) $<


run_main: $(CLASSES)
	$(JAVA) Main

run: run_main 

clean:
	rm -f *.class
