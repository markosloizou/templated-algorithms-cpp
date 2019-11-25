#ifndef TSORT_H
#define TSORT_H

#include <utility> 
#include <map> 
#include <vector>
#include <stack>

typedef enum visitState
{
    not_visited,
    is_visiting, 
    visited
} visitState; 

class topologicalSort
{
private:
    std::vector<int> vertices; //store vertices
    
    //create adjacency list representation of the graph
    std::vector<std::vector<int>> adjacencyList;
    //map each node to an int in the range of [0,n) where n is the number of vertices]
    std::map<int,int> nodeToIndex;  //used to acces adjacency list
    
    std::vector<visitState> nodeState;     //store node state for the DFS
    std::stack<int> sortedResults;         //store results

    
    
    bool cycleExists;
    
    void createNodeToIndexMap(std::vector<int> &vertices, std::vector<std::pair<int,int>> &edges);
    void createAdjacencyList(std::vector<int> &vertices, std::vector<std::pair<int,int>> &edges);
    void DFS(int start);
    
    
public:
    topologicalSort(std::vector<int> vertices, std::vector<std::pair<int,int>> edges);
    std::stack<int> sort();
    bool cycleFound();
};


#endif
