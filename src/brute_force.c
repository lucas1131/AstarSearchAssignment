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

#ifdef DEBUG
	PrintBoard(board);
	printf("\n");
	printf("\nPress ENTER...");
	getchar();
#endif

	// Limit at 50 recursive calls - each cell has 4 possible movements so for
	// max depth at 50, we have 200 recursive for each cell
	fprintf(stderr, "[debug](Backtrack): Depth: %d\n", depth);
	if(depth > 50) {	
		fprintf(stderr, "[debug](Backtrack): Path exceeded maximum depth\n");
		return false;
	}
	if(IsSolved(board)){
		
		fprintf(stderr, "\n[debug](Backtrack): Board is solved!\n");
		PrintBoard(board);
		printf("\n");

		solution[depth] = '\0';
		printf("%s\n", solution);
		return true;
	}

	/* 	Next step
		Call backtrack for each possible movement while avoiding going back
	*/

	// Move up
	if(prev != 'D' && row){

		fprintf(stderr, "[debug](Backtrack): Moving up\n\n");
		solution[depth] = 'U';
		Swap(board, row, col, -1, 0);
		if(Backtrack(depth+1, -1, 0, board, solution[depth], solution))
			return true;
	}

	// Move down
	if(prev != 'U' && row < 3){

		fprintf(stderr, "[debug](Backtrack): Moving down\n\n");
		solution[depth] = 'D';
		Swap(board, row, col, 1, 0);
		if(Backtrack(depth+1, 1, 0, board, solution[depth], solution))
			return true;
	}

	// Move left
	if(prev != 'R' && col){

		fprintf(stderr, "[debug](Backtrack): Moving left\n\n");
		solution[depth] = 'L';
		Swap(board, row, col, 0, -1);
		if(Backtrack(depth+1, 0, -1, board, solution[depth], solution))
			return true;
	}

	// Move right
	if(prev != 'L' && col < 3){

		fprintf(stderr, "[debug](Backtrack): Moving right\n\n");
		solution[depth] = 'R';
		Swap(board, row, col, 0, 1);
		if(Backtrack(depth+1, 0, 1, board, solution[depth], solution))
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
	if(done) printf("Time: %lf\n", (clock()-time)/((double) CLOCKS_PER_SEC));
#endif

	return done;
}