main: SudokuMachine.o main.o
	g++ -o main main.o SudokuMachine.o

SudokuMachine.o: SudokuMachine.cpp SudokuMachine.hpp
	g++ -c SudokuMachine.cpp

main.o: main.cpp SudokuMachine.hpp
	g++ -c main.cpp



