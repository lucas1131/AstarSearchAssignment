/* Brute force solution source file
	Lucas Alexandre Soares n usp 9293265
	Giovanna Oliveira Guimarães nusp 9293693
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "brute_force.h"
#include "utils.h"

#define MAX_DEPTH 50

bool IsSolved(uint64 board){

	int index;

	// Check if blank is bottom right, if not, then it is not solved
	if((board >> 4*15) != 0) return false;

	for(index = 0; index < 15; index ++){

		int value = board & 15;
		board >>= 4;

		if(value != index+1) return false;
	}
	return true;
}

bool Backtrack(int depth, int row, int col, uint64 board, char prev, char *solution){

#ifdef DEBUG
	PrintBoard(board);
	printf("\n");
	printf("\nPress ENTER...");
	getchar();
#endif

	uint64 newBoard;

	// Limit at 50 recursive calls - each cell has 4 possible movements so for
	// max depth at 50, we have 200 recursive for each cell
	if(depth > MAX_DEPTH) return false;
	if(IsSolved(board)){		
		solution[depth] = '\0';
		printf("%s\n", solution);
		return true;
	}

	/* 	Next step
		Call backtrack for each possible movement while avoiding going back
	*/

	// Move up
	if(prev != 'D' && row){

		solution[depth] = 'U';
		newBoard = Swap(board, row, col, -1, 0);
		if(Backtrack(depth+1, row-1, col, newBoard, solution[depth], solution))
			return true;
	}

	// Move down
	if(prev != 'U' && row < 3){

		solution[depth] = 'D';
		newBoard = Swap(board, row, col, 1, 0);
		if(Backtrack(depth+1, row+1, col, newBoard, solution[depth], solution))
			return true;
	}
	
	// Move right
	if(prev != 'L' && col < 3){

		solution[depth] = 'R';
		newBoard = Swap(board, row, col, 0, 1);
		if(Backtrack(depth+1, row, col+1, newBoard, solution[depth], solution))
			return true;
	}
	
	// Move left
	if(prev != 'R' && col){

		solution[depth] = 'L';
		newBoard = Swap(board, row, col, 0, -1);
		if(Backtrack(depth+1, row, col-1, newBoard, solution[depth], solution))
			return true;
	}

	// No path found
	return false;
}

bool SolveBruteForce(uint64 board, int row, int col, char *solution){

#ifndef DEBUG
	// Only compute execution time if not in debug mode
	clock_t time = clock();
#endif

	bool done = Backtrack(0, row, col, board, 0, solution);
	
#ifndef DEBUG
	if(done) printf("Brute force time: %lf\n", (clock()-time)/((double) CLOCKS_PER_SEC));
#endif

	return done;
}