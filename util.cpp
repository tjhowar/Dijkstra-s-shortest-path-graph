#include "util.h"
#include "graph.h"
#include <fstream> //read file
#include <iostream>
using namespace std;

//This file implements a keyboard parser and reads values from a file

int nextCommand(int *s, int *t, int *i)
{
     char c;
     int ttest, stest,itest;
     c = getchar();
     c = toupper(c);

    //misc input
    if (c == ' ' || c == '\t' || c == '\n'){
        c = 'Z';
    }

    // Commands without extra inputs
    else if (c == 'S' || c == 'R' || c == 'W'){
        c = c;
    }

    //Read in the F s t i command
    else if (c == 'F' ){

        stest = scanf("%d", s);
        ttest = scanf("%d", t);
        itest = scanf("%d", i);

        if(stest == 0 || ttest == 0 || itest == 0){
            c = 'Z';

        }
    }

    else{
        cout << "Invalid Command" << endl;
    }

    cin.sync();
    return c;
}



// Read from Ginput.txt file.
// The first line of the file contains two integers, 'n' and 'm', which indicate the number of vertices AND the
// number of edges of the graph respectively.
// It is then followed by 'm' lines, where each line contains three integers: u, v, and w. These three integers
// indicate the information of an edge. For example, there is an edge pointing from 'u' to 'v' with weight 'w'.
//NOTE: The vertices of the graph are indexed from 1 to 'n'.
void readFile(Graph* graph) {

    int v1, e1, u, v, w;

    //Open file
    ifstream myfile;
    myfile.open("Ginput.txt");

    //get vertices and edges from file
    myfile >> v1 >> e1;
    graph->v = v1;
    graph->e = e1;

    graph->H = NULL;

    if(graph->A == NULL) {
        graph->A = new List *[v1 + 1];
    }

    for (int i = 1; i <= v1; i++) { //clear adjacency lists
        graph->A[i] = NULL;
    }

    //Read and assign input
    while (myfile >> u >> v >> w) {

        List* temp = new List;
        temp->neighbor = v;
        temp->weight = w;
        temp->next = NULL;

        if (graph->A[u] == NULL) {   //if adjacency list at node 'u' is null, then add adjacency list
            graph->A[u] = temp;
        }
        else {    //if not null, store previous neighbor/weight as next

            temp->next = graph->A[u];
            graph->A[u] = temp;
        }

    }
    myfile.close();
}

