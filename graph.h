#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H
#include <vector>
using namespace std;

//This struct implements the adjacency list of the graph.
struct List{

    int neighbor;
    int weight;
    struct List* next; //next adjacency list
};

struct Graph{

    int v; //number of vertices
    int e; //number of edges
    struct Element* H; //node
    struct List** A; //A is a pointer to an array of list pointers (adjacency list)
    vector<Element> extracted; //store extracted nodes

};

//Initialize the source and set the distance/parents for each node
void InitializeSingleSource(Graph* g, int s);

//Apply relaxation technique to min heap.
void Relax(Graph* graph, int u, int v, int w);

//Calculates values for graph and returns index of target node
int calcShortestPath(Graph* graph, int s,int t);

//retrieve index of node for use during relax technique
int findNodeIndex(Graph* graph, int node);

//prints out adjacency list
void printGraph(Graph* heap);

//print path from source node to target node
void printPath(Graph* graph, int tindex, int source);

//print length of path
void printLength(Graph* graph, int index);

//return if node is reachable or not
bool nodeReachable(Graph* graph, int s, int tindex);

#endif
