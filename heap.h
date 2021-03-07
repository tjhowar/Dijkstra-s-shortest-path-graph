#ifndef HEAP_H // prevents double declarations
#define HEAP_H
#include <iostream>
#include "graph.h"
using namespace std;


//This struct will be used to implement the min-heap.
// The min heap will keep track of the shortest distance computed for each node in the graph
struct Element{
    int node;
    int d; //distance
    int p; //parent
};

//Initialize the graph elements/nodes
void Initialize(Graph* graph, int s);

//Uses the linear time build heap algorithm to obtain a min-heap of size 'n' from the given array 'A.'
void BuildHeap(Graph* graph,Element* A, int n);

//Implements the Min-Heapify algorithm which sorts elements in an array so that they satisfy the min heap property.
void MinHeapify(Element* A, int i, int arraySize);

//used to swap node values
void swap(int *x, int *y);

// gets parent node
int parent( int i);

//Extracts the element with minimum distance in the heap
void ExtractMin(Graph* graph);

//Get the minimum node from the heap
int getMin(Graph* graph);

//Decreases the value(distance) of the 'graph' element pointed to by the 'index' to the given 'value'.
// Adjustments must also be made to make sure the graph order is maintained.
void DecreaseKey(Graph* graph, int index, int value);

#endif
