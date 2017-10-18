/* Priority Queue header file
	Lucas Alexandre Soares n usp 9293265
	Giovanna Oliveira Guimarães nusp 9293693
*/

#ifndef _PQUEUE_H_
#define _PQUEUE_H_

#define MIN_HEAP 0
#define MAX_HEAP 1

#define FULL_QUEUE -5

typedef struct pqueue PQUEUE;

PQUEUE *PQ_CreateQueue(uint capacity, uint heapOrder, int (*cmp)(const void *, const void *),
	void (*DestroyItem)(void **));

void PQ_DestroyQueue(PQUEUE **pqueue);
int PQ_Enqueue(PQUEUE *pqueue, void *item);
void *PQ_Dequeue(PQUEUE *pqueue);

#endif