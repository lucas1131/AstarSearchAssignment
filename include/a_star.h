/* A* search include file
	Lucas Alexandre Soares n usp 9293265
	Giovanna Oliveira Guimarães nusp 9293693
*/

#ifndef _A_STAR_
#define _A_STAR_

#include <stdlib.h>
#include "boolean.h"

// Static or object approach?
void SetHeuristic(float (*h)(int)) { heuristic = h; }

// Object
struct {

	float (*heuristic)(int);
	bool (*solve)(void);

} A_STAR;

A_STAR *CreateAStarSolver(){
	
}

void DestroyAStarSolver(A_STAR **as){
	
}

// Static
float (*heuristic)(int);

bool A_Star(){

	/*...*/
	heuristic(/*...*/);
}

#endif