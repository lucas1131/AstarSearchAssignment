/* A* search source file
	Lucas Alexandre Soares n usp 9293265
	Giovanna Oliveira Guimarães nusp 9293693
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "a_star.h"
#include "utils.h"

#define abs(a)  ((a) >= 0 ? (a): -(a))

typedef struct path{
	uint64 board;
	int newBoardCost;
	char movement;
	char row, col;
} Path;

// Compute full cost of placing every cell in their correct position (A* goal)
int FullCost(uint64 board){
	
	int row, col;
	int distance = 0;
	
	for (row = 0; row < 4; row ++){
		for (col = 0; col < 4; col++){
			int value = board & 15;
			board >>= 4;

            // skip the empty cell as once all other cells are in place
            // then the empty cell must also be in place.
			if(value != 0){
				int expectedValueRow = (value-1) / 4;
				int expectedValueCol = (value-1) % 4;
				distance += abs(col-expectedValueCol) + abs(row-expectedValueRow);
			}
		}
	}
	return distance;
}

// A* heuristic
// Compute the cost of placing cell at [valueRow, valueCol] at it's correct pos
inline int deltaCost(uint64 board, int row, int col, int valueRow, int valueCol){
	int value = GetFrom(board, valueRow, valueCol);
	int expectedValueRow = (value-1)/4;
	int expectedValueCol = (value-1)%4;
	return ((abs(row-expectedValueRow) + abs(col-expectedValueCol)) - 
			(abs(valueRow-expectedValueRow) + abs(valueCol-expectedValueCol)));
}

uint64 Swap(uint64 board, int srcRow, int srcCol, int destRow, int destCol){
	return SetBoard(SetBoard(board, srcRow+destRow, srcCol+destCol, 0), 
					srcRow, srcCol, 
					GetFrom(board, srcRow+destRow, srcCol+destCol));
}

/*Calculate cost (min moves) of new state using delta method to save time */ 	
// row2 and col2 are the position of the cell to be moved
void GetPathCost(uint64 board, int row, int col, 
				 int row2, int col2, char movement, Path *path, 
				 int totalCost, int depth, int limit, int *validPaths){
	int newBoardCost = totalCost+deltaCost(board, row, col, row+row2, col+col2);
	
	if(depth + newBoardCost <= limit){
		SetBoard(SetBoard(board, row+row2, col+col2, 0), 
						   row, col,
						   GetFrom(board, row+row2, col+col2));
    	uint64 newBoard = Swap(board, row, col, row2, col2);
		
		path->row = row2+row;
		path->col = col2+col;
		path->movement = movement;
		path->newBoardCost = newBoardCost;
		path->board = newBoard;
		(*validPaths)++;
	}
}

bool dfs(int depth, int totalCost, int limit, 
		 int row, int col, uint64 board, char prev, char *solution){

#ifdef DEBUG
	PrintBoard(board);
	printf("\n");
	getchar();
#endif

	Path paths[4];
	int validPaths = 0;

    // cost of current state is zero means we reached the goal
	if(totalCost == 0){
		solution[depth] = 0;
		printf("%s\n", solution);
		return true;
	}
	
	// Calculate cost for each possibility, but make sure we don't go back to 
	// where we came from
	if(prev != 'D' && row)
		GetPathCost(board, row, col, -1, 0, 'U', &paths[validPaths], 
					totalCost, depth, limit, &validPaths);
	
	if(prev != 'U' && row < 3)
		GetPathCost(board, row, col, 1, 0, 'D', &paths[validPaths], 
					totalCost, depth, limit, &validPaths);
	
	if(prev != 'R' && col)
		GetPathCost(board, row, col, 0, -1, 'L', &paths[validPaths], 
					totalCost, depth, limit, &validPaths);
	
	if(prev != 'L' && col < 3)
		GetPathCost(board, row, col, 0, 1, 'R', &paths[validPaths], 
					totalCost, depth, limit, &validPaths);

	int i, j;
	int maxidx = 0;

	// Find lowest cost path 
	for(i = 0; i < validPaths; i++){
		for(j = 0; j < validPaths; j++){
			if( (paths[j].movement >= 0) && 
				(paths[j].newBoardCost < paths[maxidx].newBoardCost) ){
				maxidx = j;
			}
		}
	
		solution[depth] = paths[maxidx].movement;

		// Next step
  		bool done = dfs(depth+1, paths[maxidx].newBoardCost, limit, 
						paths[maxidx].row, paths[maxidx].col, 
			            paths[maxidx].board, solution[depth], solution);

  		// If done return
		if(done) return true;

		// Invalidate path
		paths[maxidx].movement = -1;
		maxidx = (maxidx+1)%validPaths;
	}

	return false;
}

bool SolveAStar(uint64 board, int row, int col, char *solution){

	clock_t time = clock();
    // min moves needed to transit to goal state
	int totalCost = FullCost(board);

    // PDF says to try up to 50 
	for(int limit = totalCost; limit <= 50; limit++){
		fprintf(stderr, "increasing limit\n");
		bool done = dfs(0, totalCost, limit, row, col, board, 0, solution);
		if(done){
			printf("Time: %lf\n", (clock()-time)/((double) CLOCKS_PER_SEC));
			return true;
		}
	}
	return false;
}