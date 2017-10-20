/* Priority Queue source file
	Lucas Alexandre Soares
	n usp 9293265
*/

#include <stdio.h>
#include <stdlib.h>

#include "pqueue.h"

#define getLeft(x)	(2*(x) + 1)
#define getRight(x)	(2*(x) + 2)
#define getParent(x)	((x)/2)

typedef unsigned int uint;

struct pqueue {

	uint size;	// Actual size
	uint capacity;	// Maximum capacity
	void **item;	// Items vector

	void (*Heapify)(PQUEUE *, int);	// Heapify function (max or min heap)

	int (*cmp)(const void *item1, const void *item2);	// Item comparator function
	void (*DestroyItem)(void **);	// Item destructor

};

void _internal_MinHeapify(PQUEUE *, int);
void _internal_MaxHeapify(PQUEUE *, int);


PQUEUE *PQ_CreateQueue(uint capacity, uint heapOrder,
	int (*cmp)(const void *, const void *),
	void (*DestroyItem)(void **)){

	if(!cmp) return NULL;
	if(heapOrder != MIN_HEAP && heapOrder != MAX_HEAP)
		return NULL;

	PQUEUE *pqueue = (PQUEUE *) malloc(sizeof(PQUEUE));

	if(!pqueue) return NULL;

	pqueue->size = 0;
	pqueue->capacity = capacity;
	pqueue->item = (void **) calloc(capacity, sizeof(void **));
	pqueue->cmp = cmp;

	if(heapOrder) pqueue->Heapify = &_internal_MaxHeapify;
	else pqueue->Heapify = &_internal_MinHeapify;

	return pqueue;
}

void _internal_MinHeapify(PQUEUE *pqueue, int index){

	void *aux;

	uint left, right, min;

	left = getLeft(index);
	right = getRight(index);

	// Find minimum value
	if(pqueue->cmp(pqueue->item[left], pqueue->item[index]) < 0 &&
		left < pqueue->size) min = left;
	else min = index;

	if(pqueue->cmp(pqueue->item[right], pqueue->item[min]) < 0 &&
		left < pqueue->size) min = left;

	// Swap if index is not the minimum
	if(min != index){

		aux = pqueue->item[min];
		pqueue->item[min] = pqueue->item[index];
		pqueue->item[index] = aux;
		pqueue->Heapify(pqueue, min);
	}
}

void _internal_MaxHeapify(PQUEUE *pqueue, int index){

	void *aux;

	uint left, right, max;

	left = getLeft(index);
	right = getRight(index);

	// Find minimum value
	if(pqueue->cmp(pqueue->item[left], pqueue->item[index]) > 0 &&
		left < pqueue->size) max = left;
	else max = index;

	if(pqueue->cmp(pqueue->item[right], pqueue->item[max]) > 0 &&
		left < pqueue->size) max = left;

	// Swap if index is not the minimum
	if(max != index){

		aux = pqueue->item[max];
		pqueue->item[max] = pqueue->item[index];
		pqueue->item[index] = aux;
		pqueue->Heapify(pqueue, max);
	}
}

void PQ_DestroyQueue(PQUEUE **pqueue){

	if(!pqueue || !(*pqueue)) return;

	int i;

	if((*pqueue)->DestroyItem != NULL)
		for(i = 0; i < (*pqueue)->size; i++)
			(*pqueue)->DestroyItem( &((*pqueue)->item[i]) );

	free((*pqueue)->item);
	free(*pqueue);
	*pqueue = NULL;
}

int PQ_Enqueue(PQUEUE *pqueue, void *item) {
    
	int i;
	void *aux = NULL;

	if(pqueue->size >= pqueue->capacity) return FULL_QUEUE;

	// Adds element at the end of queue
	pqueue->item[pqueue->size] = item;
	i = pqueue->size++;

	// Swap element while parent is bigger
	while(i > 0 && pqueue->cmp(pqueue->item[i], pqueue->item[getParent(i)]) < 0) {
		aux = pqueue->item[i];
		pqueue->item[i] = pqueue->item[getParent(i)];
		pqueue->item[getParent(i)] = aux;
		i = getParent(i);
	}
}

void *PQ_Dequeue(PQUEUE *pqueue) {
	
	if(!pqueue) return NULL;

	void *item;
	
	if (pqueue->size < 1) return NULL;

	item = pqueue->item[0];
	pqueue->item[0] = pqueue->item[pqueue->size-1];
	pqueue->size--;

	pqueue->Heapify(pqueue, 0);
	return item;
}
