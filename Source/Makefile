all: Main.o SatSolver.o
	g++ Main.o SatSolver.o -o project3

SatSolver.o: SatSolver.cc
	g++ -c -std=c++11 SatSolver.cc

Main.o: Main.cc
	g++ -c -std=c++11 Main.cc

clean:
	rm -rf *o  project3