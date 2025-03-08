#include <gtest/gtest.h>
#include <sstream>

#include "dijkstras.h"
#include "ladder.h"

TEST(Dijkstras, small_txt)
{
  Graph G;
  file_to_graph("../src/small.txt", G);
  vector<int> previous(G.numVertices, UNDEFINED);
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);

  EXPECT_EQ(distances[0], 0);
  EXPECT_EQ(distances[1], 3);
  EXPECT_EQ(distances[2], 6);
  EXPECT_EQ(distances[3], 1);

  stringstream out;

  for(int dest = 0; dest < G.numVertices; ++dest)
  {
    vector<int> path = extract_shortest_path(distances, previous, dest);
    for(int i = 0; i < path.size(); ++i)
      out << path[i] << ' ';
    out << endl;
    out << "Total cost is " << distances[dest] << endl;
  }

  EXPECT_EQ(out.str(), "0 \nTotal cost is 0\n0 3 1 \nTotal cost is 3\n0 3 1 2 \nTotal cost is 6\n0 3 \nTotal cost is 1\n");
}

TEST(Dijkstras, medium_txt)
{
  Graph G;
  file_to_graph("../src/medium.txt", G);
  vector<int> previous(G.numVertices, UNDEFINED);
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);

  EXPECT_EQ(distances[0], 0);
  EXPECT_EQ(distances[1], 5);
  EXPECT_EQ(distances[2], 3);
  EXPECT_EQ(distances[3], 12);
  EXPECT_EQ(distances[4], 10);
  EXPECT_EQ(distances[5], 2);

  stringstream out;

  for(int dest = 0; dest < G.numVertices; ++dest)
  {
    vector<int> path = extract_shortest_path(distances, previous, dest);
    for(int i = 0; i < path.size(); ++i)
      out << path[i] << ' ';
    out << endl;
  }

  EXPECT_EQ(out.str(), "0 \n0 1 \n0 5 2 \n0 5 2 3 \n0 5 4 \n0 5 \n");
}

TEST(Dijkstras, large_txt)
{
  Graph G;
  file_to_graph("../src/large.txt", G);
  vector<int> previous(G.numVertices, UNDEFINED);
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);

  EXPECT_EQ(distances[0], 0);
  EXPECT_EQ(distances[1], 7);
  EXPECT_EQ(distances[2], 15);
  EXPECT_EQ(distances[3], 5);
  EXPECT_EQ(distances[4], 14);
  EXPECT_EQ(distances[5], 11);
  EXPECT_EQ(distances[6], 12);

  stringstream out;

  for(int dest = 0; dest < G.numVertices; ++dest)
  {
    vector<int> path = extract_shortest_path(distances, previous, dest);
    for(int i = 0; i < path.size(); ++i)
      out << path[i] << ' ';
    out << endl;
  }

  EXPECT_EQ(out.str(), "0 \n0 1 \n0 1 2 \n0 3 \n0 1 4 \n0 3 5 \n0 3 5 6 \n"); 
}

TEST(Ladder, REPLACE)
{

}