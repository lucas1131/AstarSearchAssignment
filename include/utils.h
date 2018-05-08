/* Utility functions header file
 * Gabriel Simmel Nascimento             9050232
 * Giovanna Oliveira Guimarães           9293693
 * José Augusto Noronha de Menezes Neto  9293049
 * Julia Diniz Ferreira                  9364865
 * Lucas Alexandre Soares                9293265
 * Otávio Luis Aguiar                    9293518
 * Rafael Augusto Monteiro               9293095
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#define abs(a)  ((a) >= 0 ? (a): -(a))

typedef long long unsigned uint64;

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

void GetBlank(uint64 board, int *retRow, int *retCol);
void PrintBoard(uint64 board);
uint64 Swap(uint64 board, int srcRow, int srcCol, int destRow, int destCol);

#endif
