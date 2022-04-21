#Makefile

algorithm.o: algorithm.cpp algorithm.h
  g++ -c algorithm.cpp
  
main.o: main.cpp algorithm.h
  g++ -c main.cpp

indianpoker: algorithm.o main.o
  g++ algorithm.o main.o -o indianpoker
