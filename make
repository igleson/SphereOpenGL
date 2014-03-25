all:
	g++ sphere.cpp -lX11 -lGL -lGLU -lglut -g -Wall -O2 -o sphere
	./sphere
