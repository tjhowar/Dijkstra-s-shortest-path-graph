#include "graph.h"
#include "heap.h"
#include <iostream>
#include <limits> //for infinity
#include <vector>
using namespace std;

// This file implements the graph portion of the program.


//Print out the graph adjacency list
void printGraph(Graph* graph){

    //print number of vertices and edges
    cout << graph->v << " " << graph->e << endl;

    //loop through adjacency list and print it out
    for (int i = 1; i <= graph->v; i++) {

        cout << i << " : ";
        List* temp = graph->A[i];

        while(temp!= NULL){

            cout << "(" << temp->neighbor << ", " << temp->weight << ")" ;
            if(temp->next){
                cout << "; ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

}


//Initialize the source and set the initial distance/parents for each node
void InitializeSingleSource(Graph* g, int s){

    int infinity = std::numeric_limits<int>::max();

    for (int i = 1; i <= g->v ; i++){
        g->H[i].d = infinity;
        g->H[i].p = 0;
        g->H[i].node = i;
    }

    //set source node values
    g->H[s].d = 0;
    g->H[s].p = s;

}


//Apply relaxation technique to min heap.
void Relax(Graph* graph,int u, int v, int w){

    int infinity = std::numeric_limits<int>::max();
    int findu = findNodeIndex(graph,u);
    int findv = findNodeIndex(graph,v);
    int currentNodeDistance = graph->H[findu].d;
    int currentNodeDistPlusWeight = graph->H[findu].d + w;
    bool infinDist = (currentNodeDistance == infinity);


    //Apply new distance to node
    if( (graph->H[findv].d > currentNodeDistPlusWeight)  && infinDist == false){

        DecreaseKey(graph,findv,currentNodeDistPlusWeight);

        //update index
        findu = findNodeIndex(graph,u);
        findv = findNodeIndex(graph,v);

        //set parent
        graph->H[findv].p = graph->H[findu].node;

    }

}


//Calculates values for graph and returns index of target node
int calcShortestPath(Graph* graph, int s,int t){

    //clear extracted nodes if needed
    if(graph->extracted.size() > 0){
        graph->extracted.clear();
    }

    //Initialize nodes, build heap
    Initialize(graph,s);

    int minNode;//get node with smallest distance in graph
    int targetNodeIndex = -1; //index within extracted vector for target node
    int graphSize = graph->v ;

    //loop through nodes, find min node and apply relaxation as needed
    for (int i = 1; i <= graphSize; i++ ) {

        if( i == 1){
            minNode = s;
        }else {
            minNode = getMin(graph);
        }

        //get adjacency list
        List *temp = new List;

        //Apply relaxation if min node has adjacency list
        if (graph->A[minNode] != NULL) {

            temp->neighbor = graph->A[minNode]->neighbor;
            temp->weight = graph->A[minNode]->weight;
            temp->next = graph->A[minNode]->next;

            Relax(graph, minNode, temp->neighbor, temp->weight);

            while (temp->next != NULL) {

                temp->neighbor = temp->next->neighbor;
                temp->weight = temp->next->weight;
                temp->next = temp->next->next;
                Relax(graph, minNode, temp->neighbor, temp->weight);

            }
        }

        //Extract min node after done with calculations
        ExtractMin(graph);
    }

    //Set graph size back to normal
    graph->v = graphSize;


    //Get target node index after all calculations have finished
    for (int i = 0; i < graph->extracted.size() ; i++) {

        if(graph->extracted[i].node == t){
            targetNodeIndex = i;

       }
    }

    return targetNodeIndex;
}


//print length of path
void printLength(Graph* graph, int index){

    cout << "LENGTH: " << graph->extracted[index].d << endl;
}


//print path from source node to target node
void printPath(Graph* graph, int tindex, int source){

    vector<int> path; // store path
    int sourceIndex;

    //Get source node
    for (int i = 0; i < graph->extracted.size() ; i++) {

        if(graph->extracted[i].node == source){
            sourceIndex= i;
            break;
        }

    }

    //Add target node to path
    path.push_back(graph->extracted[tindex].node);

    int targetIndex = tindex;

    //Build path of nodes by traversing parent nodes
    while( graph->extracted[targetIndex].node != graph->extracted[sourceIndex].p){

        for (int i = 0; i < graph->extracted.size() ; i++) {

            if(graph->extracted[i].node == graph->extracted[targetIndex].p){

                targetIndex = i;
                path.push_back(graph->extracted[targetIndex].node);
                break;
            }

        }
    }


    int start = path.size() - 1;
    
    //Output path from node 's' to 't'
    for(int i = start; i >= 0; i --){

        if(i == start){
            cout << "PATH: ";
        }

        if(i == 0){
            cout << path[i] << endl;
        }
        else {
            cout << path[i] << ", " ;
        }
    }

}


//return if node is reachable or not
bool nodeReachable(Graph* graph, int s, int tindex){


    vector<int> path; //store path
    bool reachable = false;
    int sourceIndex;

    //Do not do calculation if target index was invalid (-1)
    if(tindex != -1 ) {

        //get source node
        for (int i = 0; i < graph->extracted.size() ; i++) {

            if (graph->extracted[i].node == s) {
                sourceIndex = i;
                break;
            }

        }

        //Add target node to path
        path.push_back(graph->extracted[tindex].node);

        int targetIndex = tindex;

        //If earlier calc returned -1 and 's' node has no adj list or the target nodes parent is 0
        // the node is unreachable
        bool sourceNodeUnreachable = (graph->A[s] == NULL || graph->extracted[tindex].p == 0);

        if (sourceNodeUnreachable == false) {

            //Build path of nodes by traversing parent nodes
            while (graph->extracted[targetIndex].node != graph->extracted[sourceIndex].p) {


                for (int i = 0; i < graph->extracted.size() ; i++) {

                    if (graph->extracted[i].node == graph->extracted[targetIndex].p) {

                        targetIndex = i;
                        path.push_back(graph->extracted[targetIndex].node);
                        break;
                    }

                }

            }

            //If source node is in path, the node is reachable
            for (int i = path.size() - 1; i >= 0; i--) {

                if (path[i] == s) {
                    reachable = true;
                }
            }
        }
    }
    return reachable;
}


//retrieve index of node for use during relax technique
int findNodeIndex(Graph* graph, int node){

    int n = 0;
    int size = graph->v ;

    for (int i = 1; i <= size  ; i++) {

        if (graph->H[i].node == node) {
            n = i;
            break;
        }
    }
    return n;
}
