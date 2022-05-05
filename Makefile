#Makefile
#..
FLAGS = -pedantic-errors -std=c++11

algorithm.o: algorithm.cpp algorithm.h
  g++ $(FLAGS) -c algorithm.cpp
  
main.o: main.cpp algorithm.h
  g++ $(FLAGS) -c main.cpp

indianpoker: algorithm.o main.o
  g++ $(FLAGS) algorithm.o main.o -o indianpoker

clean:
  rm -f indianpoker algorithm.o main.o indianpoker.tgz

tar:
  tar -czvf indianpoker.tgz *.cpp *.h
  
.PHONY: clean tar
