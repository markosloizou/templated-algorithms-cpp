#ifndef TEMPLATEDTOPOLOGICALSORT_H
#define TEMPLATEDTOPOLOGICALSORT_H

#include <utility> 
#include <map> 
#include <vector>
#include <stack>


#include <iostream>

typedef enum visitState
{
    not_visited,
    is_visiting, 
    visited
} visitState; 

template <typename T> 
class topologicalSort
{
private:
    std::vector<T> vertices; //store vertices
    
    //create adjacency list representation of the graph
    std::vector<std::vector<int>> adjacencyList;
    //map each node to an int in the range of [0,n) where n is the number of vertices]
    std::map<T,int> nodeToIndex;  //used to acces adjacency list
    
    std::vector<visitState> nodeState;     //store node state for the DFS
    std::stack<T> sortedResults;         //store results

    
    
    bool cycleExists;
    
    void createNodeToIndexMap(std::vector<T> &vertices, std::vector<std::pair<T,T>> &edges);
    void createAdjacencyList(std::vector<T> &vertices, std::vector<std::pair<T,T>> &edges);
    void DFS(int start);
    
    
public:
    topologicalSort(std::vector<T> vertices, std::vector<std::pair<T,T>> edges);
    std::stack<T> sort();
    bool cycleFound();
};


#endif
