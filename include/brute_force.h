/* Brute force solution header file
	Lucas Alexandre Soares n usp 9293265
	Giovanna Oliveira Guimarães nusp 9293693
*/

#ifndef _BRUTE_FORCE_H_
#define _BRUTE_FORCE_H_

#include "utils.h"

bool IsSolved(uint64 board);
bool SolveBruteForce(uint64 board, int row, int col, char *solution);

#endif