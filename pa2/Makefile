#------------------------------------------------------------------------------
# Spencer Albrecht
# salbrech
# PA1 CS101
# Makefile for CMPS 101 Programming Assignment 2
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

submit:
	submit cmps101-pt.w17 pa2 List.c ListClient.c List.h Lex.c Makefile README

check:
	ls /afs/cats.ucsc.edu/class/cmps101-pt.w17/pa2/salbrech
