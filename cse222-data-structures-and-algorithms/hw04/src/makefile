JC = javac
JFLAGS = -classpath .
JD = javadoc
JDFLAGS = -protected -splitindex -use -author -version -d ./javadoc
RM = rm -f
JR = java

CLASSES = \
		Directory.java \
		File.java \
		Main.java \
		FileSystem.java \
		FileSystemElement.java \


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