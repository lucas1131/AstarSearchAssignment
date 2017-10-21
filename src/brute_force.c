/* Brute force solution source file
	Lucas Alexandre Soares n usp 9293265
	Giovanna Oliveira Guimarães nusp 9293693
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "brute_force.h"
#include "utils.h"

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

#ifdef debug
	PrintBoard(board);
	printf("\n");
	printf("\nPress ENTER...");
	getchar();
#endif

	// Limit at 50 steps
	if(depth > 50) return false;
	if(IsSolved(board)){
		solution[depth] = '\0';
		printf("%s\n", solution);
		return true;
	}
	
	solution[depth] = 'L';

	// Next step
	// bool done = Backtrack(depth+1, paths[maxidx].newBoardCost, limit, 
	// 						 paths[maxidx].row, paths[maxidx].col, 
	// 						 paths[maxidx].board, solution[depth], solution);

	// If done return
	// if(done) return true;

	// Invalidate path
	// paths[maxidx].movement = -1;

	return false;
}

bool SolveBruteForce(uint64 board, int row, int col, char *solution){

#ifndef DEBUG
	// Only compute execution time if not in debug mode
	clock_t time = clock();
#endif

	bool done = Backtrack(0, row, col, board, 0, solution);
	
#ifndef DEBUG
	if(done) printf("Time: %lf\n", (clock()-time)/((double) CLOCKS_PER_SEC));
#endif

	return done;
}