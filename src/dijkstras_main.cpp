#include "dijkstras.h"

int main()
{
    Graph G;
    file_to_graph("../src/small.txt", G);

    cout << "Dijkstras" << endl;

    vector<int> previous(G.numVertices, UNDEFINED);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    for(int dest = 0; dest < G.numVertices; ++dest)
    {
        vector<int> path = extract_shortest_path(distances, previous, dest);
        print_path(path, distances[dest]);
        cout << endl;
    }
}