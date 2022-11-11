##########################
# Makefile for Project 5 # 
#                        #
# Jorden Anfinson        #
# Eduardo Jara           #
# Jamaal Wairegi         #
#                        #
# CS 271 01              #
#                        #
# Prof. Stacey Truex     #
#                        #
# 11.11.2022             #
##########################

CPPOPTIONS = -std=c++11 -g -Wall

all: test

# ./test	
test: test_graph.o vertex.o graph.o
	g++ -o test test_graph.o vertex.o graph.o

test_graph.o: test_graph.cpp vertex.cpp graph.cpp
	g++ $(CPPOPTIONS) -c test_graph.cpp
	
graph.o: graph.cpp
	g++ $(CPPOPTIONS) -c graph.cpp
	
vertex.o: vertex.cpp
	g++ $(CPPOPTIONS) -c vertex.cpp

clean:
	rm ./test *.o
