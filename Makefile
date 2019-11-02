CC=g++
FLAGS= -g -lglut -lGL -lGLU

all: anagamma

anagamma: *.cpp
	$(CC)  *.cpp -o test $(FLAGS)

clean: 
	rm *.o test
