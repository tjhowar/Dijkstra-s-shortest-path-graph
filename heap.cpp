#include "heap.h"
#include <iostream>
using namespace std;
//This file implements all functions of the min heap


//Initialize nodes of graph
void  Initialize(Graph* graph, int s){

    //Initialize elements
   if(graph->H == NULL) {
        graph->H = new Element[graph->v + 1]; //initialize elements.
    }

    //Initialize nodes of graph
    InitializeSingleSource(graph, s);

    //Build min heap of nodes
    BuildHeap(graph,graph->H,graph->v);
}


//Uses the linear time build heap algorithm to obtain a min-heap of size 'n' from the given array 'A.'
void BuildHeap(Graph* graph,Element* A, int n){

    int arraySize = n ;

    //Go through all non-leaf nodes and run Min-Heapify on them
    for (int i = arraySize / 2; i != 0; i--) {
        MinHeapify(A, i, n);
    }

}

//Implements the Min-Heapify algorithm which sorts elements in an array so that they satisfy the min heap property.
void MinHeapify(Element* A, int i, int arraySize){

    int smallest = 0; //smallest value
    int left = 2*i; //left child node
    int right = (2*i + 1); //right child node

    //maintain heap property
    if(left <= arraySize && A[left].d < A[i].d){
        smallest = left;
    }
    else{
        smallest = i;
    }
    if(right <= arraySize && A[right].d < A[smallest].d){

        smallest = right;
    }
    if(smallest != i){

        //swap values, make recursive call to min-heapify
        swap(&A[i].node, &A[smallest].node);
        swap(&A[i].d, &A[smallest].d);
        swap(&A[i].p, &A[smallest].p);

        MinHeapify(A, smallest, arraySize);
    }
}


//get parent node
int parent( int i){
    return (i) / 2;
}


//Extracts the element with minimum distance in the heap
void ExtractMin(Graph* graph){

    int end = graph->v + 1;

    //extract node
    graph->extracted.push_back(graph->H[1]);

    //delete node
    graph->H[1].node = graph->H[end].node;
    graph->H[1].p = graph->H[end].p;
    graph->H[1].d = graph->H[end].d;

    graph->H[1].node = graph->H[end - 1].node;
    graph->H[1].p = graph->H[end - 1].p;
    graph->H[1].d = graph->H[end - 1].d;


    //Make sure that the remaining elements still satisfy the heap property.
    graph->v --;
    MinHeapify(graph->H, 1, graph->v);

}

//Get the minimum node from the heap
int getMin(Graph* graph){

    return graph->H[1].node;
}


//Decreases the value(distance) of the 'graph' element pointed to by the 'index' to the given 'value.'
// Adjustments must also be made to make sure the heap order is maintained.
void DecreaseKey(Graph* graph, int index, int value){

     //set new value
    int i = index;
    graph->H[i].d = value;

    //Maintain min-heap property by switching parent node and index node as necessary
     while( i > 1 && graph->H[parent(i)].d > graph->H[i].d){

         swap(&graph->H[i].node, &graph->H[parent(i)].node);
         swap(&graph->H[i].d, &graph->H[parent(i)].d);
         swap(&graph->H[i].p, &graph->H[parent(i)].p);
         i = parent(i);

     }

}


//swap values at nodes
void swap(int *x, int *y){

    int temp = *x;
    *x = *y;
    *y = temp;
}

