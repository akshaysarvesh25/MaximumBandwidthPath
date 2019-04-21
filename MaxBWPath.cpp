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
  Graph_test[0].insert(0,99999);
  Graph_test[0].insert(1,20);
  Graph_test[0].insert(2,70);


  Graph_test[1].insert(1,99999);
  Graph_test[1].insert(3,3);
  Graph_test[1].insert(0,20);

  Graph_test[2].insert(2,99999);
  Graph_test[2].insert(0,70);
  Graph_test[2].insert(3,100);

  Graph_test[3].insert(3,99999);
  Graph_test[3].insert(1,3);
  Graph_test[3].insert(2,100);



  for(unsigned int i = 0;i<=3;i++)
  {
  cout<<i<<"->";
  Graph_test[i].display();
  }

  /*
  Graph_test[0].ViewNodeStatus();
  Graph_test[1].ViewNodeStatus();
  Graph_test[2].ViewNodeStatus();
  */

  /* Make all nodes of the graph unseen */
  for(unsigned int count = 0;count<=3;count++)
  {
    Graph_test[count].MakeNodesUnseen();
    //cout<<"count is : "<<count<<endl;
  }

  /*
  Graph_test[0].ViewNodeStatus();
  Graph_test[1].ViewNodeStatus();
  Graph_test[2].ViewNodeStatus();
  */

  Graph_test[0].MakeNodesIntree();

  Graph_test[0].SetNodeBandwidth(99999);

  int Node_prev = 0;

  std::vector<int> AdjacentNodes = Graph_test[0].GetAdjacentNodes();
  std::vector<int> AdjacentNodeWeights = Graph_test[0].GetAdjacentNodesWeights();
  /*
  if(Heap_test->SizeOfHeapIsZero() == 1)
  {
    cout<<"Heap is null"<<endl;
    cout<<Heap_test->SizeOfHeapIsZero()<<endl;
  }*/

  /*
  Graph_test[0].ViewNodeStatus();
  Graph_test[1].ViewNodeStatus();
  Graph_test[2].ViewNodeStatus();
  */
  for(unsigned int count = 1;count<=(AdjacentNodes.size()-1);count++)
  {

    int AdjNode = (int)AdjacentNodes[count];
    cout<<"Nodename : "<<AdjNode<<endl;
    cout<<"Count : "<<count<<endl;
    int AdjNodeWeight = (int)AdjacentNodeWeights[count];
    Graph_test[AdjNode].MakeNodesFringe();
    Graph_test[AdjNode].SetDad(0);
    Graph_test[AdjNode].GetDad();
    Graph_test[AdjNode].SetNodeBandwidth(AdjNodeWeight);
    bool b = Heap_test->Insert(AdjNode,AdjNodeWeight);

  }

  cout<<"\n__First stage done__\n"<<endl;

  /* Printing the heap data structure */
  Heap_test->print();
  cout<<"\n\nStarting the algorithm.. \n"<<"_____"<<endl;

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
    //std::vector<int> AdjacentNodes = Graph_test[Node].GetAdjacentNodesWithout(Node_prev);
    std::vector<int> AdjacentNodes = Graph_test[Node].GetAdjacentNodes();//Without(Node_prev);
    std::vector<int> AdjacentNodeWeights = Graph_test[Node].GetAdjacentNodesWeights();//Without(Node_prev);
    Node_prev = Node;

    for(unsigned int count = 1;count<AdjacentNodes.size();count++)
    {
      int AdjNode = (int)AdjacentNodes[count];
      //cout<<"Status of the node "<<AdjNode<<" : "<<endl;
      Graph_test[AdjNode].ViewNodeStatus();

      int AdjNodeBW1 = Graph_test[AdjNode].GetBandWidth();
      int BW_node1 = Graph_test[Node].GetBandWidth();
      int AdjNode_Weight1 = Graph_test[Node].GetWeightOfAdjNode(AdjNode);/* TODO */

      cout<<"BW_Adj Node, BW_Node, AdjNode_Weight "<<AdjNodeBW1<<" , "<<BW_node1<<" , "<<AdjNode_Weight1<<endl;

      if(Graph_test[AdjNode].IsNodeUnseen() == true)
      {
        cout << "\033[1;32mNode unseen  \033[0m"<<AdjNode<<std::endl;
        Graph_test[AdjNode].MakeNodesFringe();
        Graph_test[AdjNode].SetDad(Node);
        //int BW_node = Graph_test[Node].GetBandWidth();
        //int AdjNode_Weight = Graph_test[AdjNode].GetWeight();
        cout<<"Weight of the adjacent node and bandwidth of the current node : "<<AdjNode_Weight1<<" & "<<BW_node1<<endl;
        Graph_test[AdjNode].SetNodeBandwidth(std::min({BW_node1,AdjNode_Weight1}));
        int AdjNodeBW = Graph_test[AdjNode].GetBandWidth();
        Heap_test->Insert(AdjNode,AdjNodeBW);
        Heap_test->print();
      }

      else if((Graph_test[AdjNode].IsNodeFringe() == true)&&(AdjNodeBW1<(std::min({BW_node1,AdjNode_Weight1}))))
      {
        cout << "\033[1;32mNode is fringe : \033[0m"<<AdjNode<<std::endl;
        Heap_test->Delete(Heap_test->position[AdjNode]);
        Heap_test->print();
        Graph_test[AdjNode].SetDad(Node);
        //ToDo
        Graph_test[AdjNode].SetNodeBandwidth(std::min({BW_node1,AdjNode_Weight1}));
        int AdjNodeBW2 = Graph_test[AdjNode].GetBandWidth();
        Heap_test->Insert(AdjNode,AdjNodeBW2);
        Heap_test->print();

      }

      else
      {
        std::cout << "\033[1;31mNot necessary to process Element of heap : \033[0m"<<AdjNode<<std::endl;
      }

    }
    cout<<"____"<<endl;
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
