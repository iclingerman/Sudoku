# Ian Clingerman 
# Makefile for Sudoku Solver Program

# OBJS = src/Driver.cpp src/Board.cpp
OBJS = src/main.cpp src/Board.cpp
CC = g++
OUTFILE = bin/SudokuSolver

INCLUDE_PATHS = -ISFML/include
LINKER_PATHS = -LSFML/lib
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system



all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LINKER_PATHS) $(LINKER_FLAGS) -o $(OUTFILE)

run: 
	./$(OUTFILE)

clean:
	rm bin/*.exe