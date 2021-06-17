# Ian Clingerman 
# Makefile for Sudoku Solver Program

OBJS = src/Driver.cpp src/Board.cpp
CC = g++
OUTFILE = bin/SudokuSolver
FILE = out

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUTFILE)

run: 
	./$(OUTFILE)

clean:
	rm bin/*