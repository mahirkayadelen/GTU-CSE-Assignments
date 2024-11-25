JAVAC = javac
JAVA = java
FLAGS = -g

SOURCES = AVLTree.java Stock.java StockDataManager.java Main.java GUIVisualization.java

CLASSES = AVLTree.class Stock.class StockDataManager.class Main.class GUIVisualization.class

all: run

%.class: %.java
	$(JAVAC) $(FLAGS) $<


run_main: $(CLASSES)
	$(JAVA) -Xint Main input.txt

run_gui: $(CLASSES)
	-$(JAVA) GUIVisualization

run: run_main run_gui

clean:
	rm -f *.class
