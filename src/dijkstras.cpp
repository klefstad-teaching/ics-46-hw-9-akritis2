#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);

    distances[source] = 0;
    previous[source] = UNDEFINED;
    
    // Using greater<pair<int, int>> to make pq a minHeap.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});

    while(!minHeap.empty())
    {
        int u = minHeap.top().second;
        minHeap.pop();
        
        if(visited[u])
            continue;
        
        visited[u] = true;

        for(Edge e : G[u])
        {
            int v = e.dst;
            int weight = e.weight;

            if(!visited[v] && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    /*
    // If distance to destination is INF, destination has not been reached.
    if (distances[destination] == INF)
        return {}; // Return empty path.
    */

    vector<int> path;

    for(int curr = destination; curr != UNDEFINED; curr = previous[curr])
        path.push_back(curr);

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    for(int i = 0; i < v.size(); ++i)
        cout << v[i] << ' ';

    cout << endl;

    cout << "Total cost is " << total << endl;
}