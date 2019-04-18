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

  Heap<int> *Heap_test = new Heap<int>();

  /* Creating graphs of 5000 nodes as an adjacency list */
  LinkedList<int> *Graph_1 = new LinkedList<int>[NUMBER_OF_VERTICES];
  LinkedList<int> *Graph_2 = new LinkedList<int>[NUMBER_OF_VERTICES];

  LinkedList<int> *Graph_test = new LinkedList<int>[5];
  Graph_test[0].insert(1,20);
  Graph_test[1].insert(0,20);

  Graph_test[0].insert(2,70);
  Graph_test[2].insert(0,70);
  //Graph_test[0].insert(4,5);
  Graph_test[1].insert(3,3);
  Graph_test[3].insert(1,3);

  Graph_test[2].insert(3,1);
  Graph_test[3].insert(2,1);

  //Graph_test[0].insert(4,2);

  /*
  Graph_test[0].ViewNodeStatus();
  Graph_test[1].ViewNodeStatus();
  Graph_test[2].ViewNodeStatus();
  */

  /* Make all nodes of the graph unseen */
  for(unsigned int count = 0;count<=3;count++)
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
  std::vector<int> AdjacentNodeWeights = Graph_test[0].GetAdjacentNodesWeights();
  /*
  if(Heap_test->SizeOfHeapIsZero() == 1)
  {
    cout<<"Heap is null"<<endl;
    cout<<Heap_test->SizeOfHeapIsZero()<<endl;
  }*/

  for(unsigned int count = 0;count<AdjacentNodes.size();count++)
  {
    int AdjNode = (int)AdjacentNodes[count];
    int AdjNodeWeight = (int)AdjacentNodeWeights[count];
    Graph_test[AdjNode].MakeNodesFringe();
    Graph_test[AdjNode].SetDad(0);
    Graph_test[AdjNode].SetNodeBandwidth(AdjNodeWeight);
    bool b = Heap_test->Insert(AdjNode,AdjNodeWeight);

  }
  /* Printing the heap data structure */
  Heap_test->print();
  cout<<"Starting the algorithm.."<<endl;
  while(Heap_test->SizeOfHeapIsZero()!=0)
  {
    int Node = Heap_test->MaxEdge();
    int weight = Heap_test->MaxWeight();
    cout<<"Node and weight : "<<Node<<" "<<weight<<endl;
    //cout<<Heap_test->SizeOfHeapIsZero()<<endl;
    Heap_test->Delete(Heap_test->position[Node]);
    Heap_test->print();
    Graph_test[Node].MakeNodesIntree();
    //cout<<Heap_test->SizeOfHeapIsZero()<<endl;
    std::vector<int> AdjacentNodes = Graph_test[Node].GetAdjacentNodes();

    for(unsigned int count = 0;count<AdjacentNodes.size();count++)
    {
      int AdjNode = (int)AdjacentNodes[count];
      cout<<"Status of the node "<<AdjNode<<" : "<<endl;
      Graph_test[AdjNode].ViewNodeStatus();

      int AdjNodeBW1 = Graph_test[AdjNode].GetBandWidth();
      int BW_node1 = Graph_test[Node].GetBandWidth();
      int AdjNode_Weight1 = Graph_test[AdjNode].GetWeight();

      if(Graph_test[AdjNode].IsNodeUnseen() == true)
      {
        Graph_test[AdjNode].MakeNodesFringe();
        Graph_test[AdjNode].SetDad(Node);
        int BW_node = Graph_test[Node].GetBandWidth();
        int AdjNode_Weight = Graph_test[AdjNode].GetWeight();
        cout<<"Weight of the adjacent node and bandwidth of the current node : "<<AdjNode_Weight<<" & "<<BW_node<<endl;
        Graph_test[AdjNode].SetNodeBandwidth(std::min({BW_node,AdjNode_Weight}));
        int AdjNodeBW = Graph_test[AdjNode].GetBandWidth();
        Heap_test->Insert(AdjNode,AdjNodeBW);
        Heap_test->print();
      }

      else if((Graph_test[AdjNode].IsNodeFringe() == true)&&(AdjNodeBW1<(std::min({BW_node1,AdjNode_Weight1}))))
      {
        Heap_test->Delete(Heap_test->position[AdjNode]);
        Heap_test->print();
        Graph_test[AdjNode].SetDad(Node);
        //ToDo
        Graph_test[AdjNode].SetNodeBandwidth(std::min({BW_node1,AdjNode_Weight1}));
        int AdjNodeBW2 = Graph_test[AdjNode].GetBandWidth();
        Heap_test->Insert(AdjNode,AdjNodeBW2);
        Heap_test->print();

      }

    }
  }

  int Node_D = 3;
  cout<<Node_D<<"<-";
  while(Graph_test[Node_D].DisplayDadNodes()!=0)
  {
    cout<<Graph_test[Node_D].DisplayDadNodes()<<"<-";
    Node_D=Graph_test[Node_D].DisplayDadNodes();
  }
  cout<<"0"<<endl;










  return 0;
}
