/* Utility functions source file
 * Gabriel Simmel Nascimento             9050232
 * Giovanna Oliveira Guimarães           9293693
 * José Augusto Noronha de Menezes Neto  9293049
 * Julia Diniz Ferreira                  9364865
 * Lucas Alexandre Soares                9293265
 * Otávio Luis Aguiar                    9293518
 * Rafael Augusto Monteiro               9293095
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void PrintBoard(uint64 board){
	int i;
	for(i = 0; i < 16; i++){
		if((board & 15) == 0) printf("%-2c ", ' ');
		else printf("%-2lld ", board & 15);
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

uint64 Swap(uint64 board, int srcRow, int srcCol, int destRow, int destCol){
	return SetBoard(
				SetBoard(board, srcRow+destRow, srcCol+destCol, 0), 
				srcRow, srcCol, 
				GetFrom(board, srcRow+destRow, srcCol+destCol)
			);
}

