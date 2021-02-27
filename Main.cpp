// 

#include <iostream>
#include "util.h"
#include "graph.h"
using namespace std;


int main()
{

    //check for if valid s-t nodes
    bool sValid;
    bool tValid;

    // values for input
    char c;
    int s, t, i;

    //create pointer to Graph struct
    Graph* graph = NULL;

    while(1){

        cin.sync();
        c = nextCommand(&s, &t, &i); //assign values to s t i

        switch (c) {

            //On reading R, the program reads in an edge weighted directed graph from file Ginput.txt,
            // builds the adjacency lists, and waits for the next command.
            case 'R':

                //Initialize graph
               if(graph == NULL) {
                    graph = new Graph;
                }

                cout << "COMMAND: " << c << endl;

                //Retrieve values from array
                readFile(graph);

                break;


            // On reading W, the program writes the graph information to the screen and waits for the
            // next command.
            case 'W':

                cout << "COMMAND: " << c << endl;

                if (graph != NULL) {
                    printGraph(graph);
                }
                else{
                    cout << "Error: graph not initialized" << endl;
                }
                break;


            // On reading F s t i the program runs Dijkstra's shortest path algorithm to compute a
            // shortest s-t path. If i = 1, it will print out the LENGTH of this shortest path to the screen.
            // If i = 0, it will print out the PATH of the shortest path to the screen. It will then wait for the
            // next command.
            case 'F':

                cout << "COMMAND: " << c << " " << s << " " << t << " " << i << endl;

                if (graph != NULL) {

                    sValid = (s >= 1 && s <= graph->v);
                    tValid = (t >= 1 && t <= graph->v);

                    if( i == 0 || i == 1){

                        if( sValid && tValid ){

                            //get index of target node for use in extracted node vector
                            int index = calcShortestPath(graph, s, t);

                            if( ( (nodeReachable(graph,s, index) == true) || s ==t) && (index != -1) ){

                                //print length or path
                                if( i == 1){

                                    if( s == t){
                                        cout << "LENGTH: " << 0 << endl;
                                    }
                                    else {
                                        printLength(graph, index);
                                    }

                                }
                                else if (i == 0){

                                    if(s == t){

                                        cout << "PATH: " << s << endl;
                                    }
                                    else {
                                        printPath(graph, index, s);
                                    }
                                }
                            }
                            else{
                                cout << "Error: node " << t << " not reachable from node " << s << endl;
                            }
                        }
                        else{
                            cout << "Error: one or more invalid nodes" << endl;
                        }

                    }
                    else{

                        if( (sValid && tValid) == false ){ //in case nodes are also invalid
                            cout << "Error: one or more invalid nodes" << endl;
                        }
                        cout << "Error: invalid flag value" << endl;
                    }
                }
                else{
                    cout << "Error: graph not initialized" << endl;
                }
                break;

            //On reading 'S', the program stops
            case 'S':
                cout << "COMMAND: " << c << endl;
               _Exit(0); //ends program

        }

    }

}
