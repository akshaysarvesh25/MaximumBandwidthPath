/**********************************
* Dijkstra's Algorihm
* Maximum Bandwidth path
*
**********************************/
#include<MaxBWPath.h>

using namespace std;

int main()
{
  /* Heap to store the graph data */
  Heap<int> *Heap1 = new Heap<int>();
  Heap<int> *Heap2 = new Heap<int>();

  /* Creating graphs of 5000 nodes as an adjacency list */
  LinkedList<int> *Graph_1 = new LinkedList<int>[NUMBER_OF_VERTICES];
  LinkedList<int> *Graph_2 = new LinkedList<int>[NUMBER_OF_VERTICES];

  LinkedList<int> *Graph_test = new LinkedList<int>[5];
  Graph_test[0].insert(1,2);
  Graph_test[0].insert(2,2);
  Graph_test[1].insert(3,3);
  Graph_test[2].insert(3,1);
  //Graph_test[0].insert(4,2);

  /*
  Graph_test[0].ViewNodeStatus();
  Graph_test[1].ViewNodeStatus();
  Graph_test[2].ViewNodeStatus();
  */

  /* Make all nodes of the graph unseen */
  for(unsigned int count = 0;count<3;count++)
  {
    Graph_test[count].MakeNodesUnseen();
  }

  /*
  Graph_test[0].ViewNodeStatus();
  Graph_test[1].ViewNodeStatus();
  Graph_test[2].ViewNodeStatus();
  */

  Graph_test[0].MakeNodesIntree();

  Graph_test[0].SetNodeBandwidth(99999);

  std::vector<int> AdjacentNodes = Graph_test[0].GetAdjacentNodes();

  for(unsigned int count = 0;count<AdjacentNodes.size();count++)
  {
    int AdjNode = (int)AdjacentNodes[count];
    Graph_test[AdjNode].MakeNodesFringe();
    Graph_test[AdjNode].SetDad(0);
    //Graph_test[AdjNode].SetNodeBandwidth();
  }







  return 0;
}
