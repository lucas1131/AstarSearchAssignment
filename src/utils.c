/* Utility functions source file
	Lucas Alexandre Soares n usp 9293265
	Giovanna Oliveira Guimarães nusp 9293693
*/

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

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

