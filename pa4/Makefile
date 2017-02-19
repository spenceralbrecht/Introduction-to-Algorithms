#------------------------------------------------------------------------------
# Spencer Albrecht
# salbrech
# PA4 CS101
# Makefile for CMPS 101 Programming Assignment 4
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

GraphTest : Graph.o List.o
	gcc -o GraphTest GraphTest.o

GraphTest.o : GraphTest.c
	gcc -c -std=c99 -Wall GraphTest.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f GraphTest GraphTest.o

submit:
	submit cmps101-pt.w17 pa4 List.c List.h Graph.c Graph.h GraphTest.c FindPath.c Makefile README

check:
	ls /afs/cats.ucsc.edu/class/cmps101-pt.w17/pa4/salbrech
