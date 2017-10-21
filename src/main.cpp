#include <stdio.h>
#include <stdlib.h>

#include "a_star.h"
#include "brute_force.h"

int main(int argc, char *argv[]){

	int i;
	int cases;
	int startRow = 1, startCol = -1;
	uint64 board;
	char solution[1024];
	
	scanf("%d", &cases);

	while(cases--){
		
		int value;
		board = 0;
		int invSum = 0;
		int has[20] = {0};

		// Check if its solvable
		for(i = 0; i < 16; i++){
			scanf("%d", &value);
			
			#ifdef DEBUG
				getchar();	// eat '\n' for step-by-step execution
			#endif

			board = SetBoard(board, i/4, i%4, value);
			has[value] = 1;

			if(value == 0){ 
				invSum += 1 + (i/4); 
				startRow = i/4; 
				startCol = i%4;
			}

			int j; 
			for(j = 1; j < value; j++){
				if(!has[j]) invSum++;
			}
		}

		// Must be even. Why? Google says so.
		if(invSum%2 == 0){

			// Solve brute force
			// if(!SolveBruteForce(board, startRow, startCol, solution))
			// 	printf("This puzzle exceeded iterations limit (Brute Force).\n");
			
			// Solve with A*
			if(!SolveAStar(board, startRow, startCol, solution))
				printf("This puzzle exceeded iterations limit (A*).\n");

		} else printf("This puzzle is not solvable.\n");
	}

	return 0;
}
