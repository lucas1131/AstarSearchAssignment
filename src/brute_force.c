// /* Brute force solution source file
// 	Lucas Alexandre Soares n usp 9293265
// 	Giovanna Oliveira Guimarães nusp 9293693
// */

// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// #include "brute_force.h"
// #include "utils.h"

// typedef struct path{
// 	uint64 board;
// 	int newBoardCost;
// 	char movement;
// 	char row, col;
// } Path;

// bool Backtracking(int depth, int totalCost, int limit, 
// 		 int row, int col, uint64 board, char prev, char *solution){

// #ifdef debug
// 	PrintBoard(board);
// 	printf("\n");
// 	printf("\nPress ENTER...");
// 	getchar();
// #endif

// 	Path paths[4];
// 	int validPaths = 0;

//     // cost of current state is zero means we reached the goal
// 	if(totalCost == 0){
// 		solution[depth] = 0;
// 		printf("%s\n", solution);
// 		return true;
// 	}
	
	
// 	solution[depth] = paths[maxidx].movement;

// 	// Next step
// 		bool done = dfs(depth+1, paths[maxidx].newBoardCost, limit, 
// 					paths[maxidx].row, paths[maxidx].col, 
// 		            paths[maxidx].board, solution[depth], solution);

// 		// If done return
// 	if(done) return true;

// 	// Invalidate path
// 	paths[maxidx].movement = -1;

// 	return false;
// }

// bool SolveBruteForce(uint64 board, int row, int col, char *solution){

// 	#ifndef DEBUG
// 		// Only compute execution time if not in debug mode
// 		clock_t time = clock();
// 	#endif

//     // min moves needed to transit to goal state
// 	int totalCost = FullCost(board);

//     // PDF says to try up to 50 
// 	for(int limit = totalCost; limit <= 50; limit++){
// 		bool done = Backtracking(0, totalCost, limit, row, col, board, 0, solution);
// 		if(done){

// 			#ifndef DEBUG
// 				printf("Time: %lf\n", (clock()-time)/((double) CLOCKS_PER_SEC));
// 			#endif

// 			return true;
// 		}
// 	}
// 	return false;
// }