JC = javac
JFLAGS = -classpath .
JD = javadoc
JDFLAGS = -protected -splitindex -use -author -version -d ./javadoc
RM = rm -f
JR = java

CLASSES = \
		Inventory.java \
		Device.java \
		Main.java \
		ExtendedDevice.java \
		SmartPhone.java \
		Laptop.java \
		SmartWatch.java \
		Headphones.java \
		TV.java \


all : Main.class run

run : 
	$(JR) Main

classes : $(CLASSES:.java=.class)

%.class : %.java
	$(JC) $(JFLAGS) $<

doc:
	$(JD) $(JDFLAGS) *.java 

clean:
	$(RM) *.class

cleandoc:
	$(RM) -r ./javadoc