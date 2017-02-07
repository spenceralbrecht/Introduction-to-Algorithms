#------------------------------------------------------------------------------
#  Spencer Albrecht
#  salbrech
#  Makefile for CMPS 101 pa3
#  Compiles all .java files in the current directory and creates an executable
#  jar file called Sparse.
#------------------------------------------------------------------------------

MAINCLASS  = ListTest
JAVAC      = javac
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS)

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)

submit:
	submit cmps101-pt.w17 pa3 Sparse.java Matrix.java List.java MatrixTest.java ListTest.java Makefile README

check:
	ls /afs/cats.ucsc.edu/class/cmps101-pt.w17/pa3/salbrech
