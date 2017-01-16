# Spencer Albrecht
# salbrech
# PA1
# Makefile for PA1
List: List.class
	echo Main-class: List > Manifest
	jar cvfm List Manifest List.class
	rm Manifest
	chmod +x List
List.class: List.java
	javac -Xlint List.java
clean:
	rm -f List List.class
submit: README Makefile List.java
	submit cmps101-pt.u17 pa1 README Makefile List.java
