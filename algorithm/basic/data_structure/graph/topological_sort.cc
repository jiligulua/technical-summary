#include <iostream>
#include <stack>

using std::stack;
using std::cout;

const int MAXVEX = 16;

typedef struct EdgeNode {
  int adjvec;
  int weight;
  struct EdgeNode* next;
}EdgeNode;

typedef struct VertexNode {
  int in;
  int data;
  EdgeNode* first_edge;
}VertexNode, AdjList[MAXVEX];

typedef struct {
  AdjList adj_list;
  int num_vertexes;
  int num_edges;
}GraphAdjList, *GraphAdjListPtr;

enum class Status {Ok, Error};

Status TopologicalSort(GraphAdjListPtr graph) {
  if (nullptr == graph || graph->num_vertexes == 0 || graph->num_edges == 0)
    return Status::Error;

  stack<int> zero_degree;
  for (int i = 0; graph->num_vertexes; ++i) {
    if (graph->adj_list[i].in == 0)
	  zero_degree.push(i);
  }

  int count = 0;
  while (!zero_degree.empty()) {
    int vertex = zero_degree.top();
	zero_degree.pop();
	cout << graph->adj_list[vertex].data << "->";
	++count;
	auto pedge = graph->adj_list[vertex].first_edge;
	while (pedge != nullptr) {
	  auto k = pedge->adjvec;
	  if (0 == (--graph->adj_list[k].in))
	    zero_degree.push(k);
	}
  }

  if (count < graph->num_vertexes) 
	return Status::Error;
  else
	return Status::Ok;
}


