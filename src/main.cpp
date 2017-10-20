/**
	Algorithm:
	IDA*
	How to represent a board state:
	Use 64-bit bitmask! Each cell is 0-15 and there are 16 cells.
	So in total 4*16 = 64 bits required! Just nice!
	Note that using an array might not be too bad either, in fact
	I don't really know which way is faster
	Use inversion method to check solvability. (Search wolfram)
	We don't really need to keep track of previous board states so as
	to avoid redundant searching of previously encountered states.
	When do we encounter previously encountered states again?
	-When we do undo the last move, i.e., LR, UD , etc.
	-Redundant cycles such as RDLU times 2
	(which causes you to go back to the original state)
	The former occurs more frequently so it is important for the 
	recursive method to avoid it. The latter is relatively rarer
	so the speed up by avoiding it is insignificant I think.
	Since we're using DFS and don't keep track of previous board states,
	the space complexity is linear.
	Conclusions: 
	Couldn't have done it without searching for help on the net...
	Also, heuristics are powerful !
	Gotchas:
	- Initial board already solved
	- Out of memory for keeping track of large number of states
	- Wasting precious time computing for non-solvable board and previously found
	  states
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define abs(a)  ((a) >= 0 ? (a): -(a))

typedef long long unsigned uint64;
typedef struct path{
	uint64 board;
	int newBoardCost;
	char movement;
	char row, col;
} Path;

const uint64 goal = 0x0fedcba987654321;  // goal state
char *solution = (char *) calloc(1024, sizeof(char));       // backtracking solution string

/* The ideia is that we can use a 64bit integer to alocate 16 values of 4 bits 
each (from 0 to 16). Each value is a 4bit integer, accessed using an index*4 
bits bitwise left "value << (index*4)"" */
inline uint64 SetBoard(uint64 board, int row, int col, int value){
    int bitwiseIndex = row*4 + col;

    // Set the mask to the index position and fill with four 1's
    uint64 mask = (uint64)15 << (4*bitwiseIndex);

    // (board & (~mask)) will null the four bits composing the number at the 
    // calculated index
    return ( (board & (~mask)) | ((uint64)value << (4*bitwiseIndex)) );
}

inline int GetFrom(uint64 board, int row, int col){    
    int bitwiseIndex = row*4 + col;  
    return ( (board >> (4*bitwiseIndex)) & 15 );
}

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
			(abs(valueRow-expectedValueRow) - abs(valueCol-expectedValueCol)));
}

void PrintBoard(uint64 board){
	int i;
    for(i = 0; i < 16; i++){
        if((board & 15) == 0) printf("%-2c ", ' ');
        else printf("%-2d ", board & 15);
        board >>= 4;
        if((i+1) % 4 == 0) printf("\n");
    }
}

void GetBlank(uint64 board, int *retRow, int *retCol){
	int row, col;
	for(row = 0; row < 4; row++){
		for(col = 0; col < 4; col++){
			if(GetFrom(board, row, col)==0){
				*retRow = row; 
				*retCol = col; 
				return;
			}
		}
	}
}

/*Calculate cost (min moves) of new state using delta method to save time */ 	
// row2 and col2 are the position of the cell to be moved
void GetPathCost(uint64 board, int row, int col, 
				 int row2, int col2, char movement, Path *path, 
				 int totalCost, int depth, int limit, int *validPaths){
	
	int newBoardCost = totalCost+deltaCost(board, row, col, row+row2, col+col2);
	
	if(depth + newBoardCost <= limit){
    	
    	uint64 newBoard = SetBoard(SetBoard(board, row+row2, col+col2, 0), 
    							   row, col,
    							   GetFrom(board, row+row2, col+col2));
		
		path->row = row2+row;
		path->col = col2+col;
		path->movement = movement;
		path->newBoardCost = newBoardCost;
		path->board = newBoard;
		(*validPaths)++;

		fprintf(stderr, "[debug](GetPathCost) Path cost for \'%c\' : %d\n", movement, path->newBoardCost);
	}
}

bool dfs(int depth, int totalCost, int limit, 
		 int row, int col, uint64 board, char prev){
	fprintf(stderr, "\n[debug](DFS): blank space in [%d, %d]\t(depth: %d)\n", row, col, depth);
	PrintBoard(board);
	fprintf(stderr, "\n");
	Path paths[4];
	int validPaths = 0;
	
	getchar();

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
	
	if(prev != 'U' && row <= 2)
		GetPathCost(board, row, col, 1, 0, 'D', &paths[validPaths], 
					totalCost, depth, limit, &validPaths);
	
	if(prev != 'R' && col)
		GetPathCost(board, row, col, 0, -1, 'L', &paths[validPaths], 
					totalCost, depth, limit, &validPaths);
	
	if(prev != 'L' && col <= 2)
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
		fprintf(stderr, "[debug](DFS): moving \'%c\'\n", solution[depth]);
  		bool done = dfs(depth+1, paths[maxidx].newBoardCost, limit, 
						paths[maxidx].row, paths[maxidx].col, 
			            paths[maxidx].board, solution[depth]);

  		// If done return
		if(done) return true;

		// Invalidate path
		paths[maxidx].movement = -1;
		maxidx = (maxidx+1)%validPaths;
	}

	fprintf(stderr, "[debug](DFS): No path found, returning false\n");
	return false;
}

bool Solve(uint64 board, int row, int col){

	getchar();

    // min moves needed to transit to goal state
	int totalCost = FullCost(board);

    // PDF says to try up to 50 
	for(int limit = totalCost; limit <= 50; limit++){
		bool done = dfs(0, totalCost, limit, row, col, board, 0);
		if(done) return true;
	}
	return false;
}

int main(int argc, char *argv[]){

	int i;
    int cases;
    int startRow = 1, startCol = -1;
	uint64 board;

    scanf("%d", &cases);

    while(cases--){
        
        int value;
        board = 0;
		int invSum = 0;
		int has[20] = {0};

		// Check if its solvable
        for(i = 0; i < 16; i ++){
            scanf("%d", &value);
            board = SetBoard(board, i/4, i%4, value);
			has[value] = 1;

			if(value == 0){ 
				invSum += 1+i/4; 
				startRow = i/4; 
				startCol = i%4;
			}

			int j; 
			for(j = 1; j < value; j ++){
				if(!has[j]) invSum ++;
			}
        }

        // Must be even. Why? Google says so.
        if((invSum%2) || !Solve(board, startRow, startCol))
        	printf("This puzzle is not solvable.\n");
    }

    free(solution);
}
