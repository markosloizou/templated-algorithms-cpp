#include "tsort.h"


/*   Topological sort takse as argumens the vertices and the directed edges of a graph.
 * The paur of edges is marked as an edges from .first to .second, indicating that
 * the .first element must be excecuted/completed before the .second element(event) can 
 * take place. 
 */

topologicalSort::topologicalSort(std::vector<int> vertices, std::vector<std::pair<int,int>> edges)
{
    this->vertices = vertices;
    createNodeToIndexMap(vertices, edges);
    createAdjacencyList(vertices, edges);
}


void topologicalSort::createNodeToIndexMap(std::vector<int> &vertices, std::vector<std::pair<int,int>> &edges)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        nodeToIndex[vertices[i]] = i;
    }
}

void topologicalSort::createAdjacencyList(std::vector<int> &vertices, std::vector<std::pair<int,int>> &edges)
{
    int n = vertices.size();
    adjacencyList = std::vector<std::vector<int>>(n, std::vector<int>());
    
    for(auto p : edges)
    {
        int from    = nodeToIndex.at(p.first);//use at for 'bound' checking;
        int to      = nodeToIndex.at(p.second);          
        
        adjacencyList[from].push_back(to);
    }
    
}

bool topologicalSort::cycleFound()
{
    return cycleExists; //needs to be called after sort! 
}

std::stack<int> topologicalSort::sort()
{
    int n = adjacencyList.size();
    
    nodeState = std::vector<visitState>(n, visitState{not_visited});
    
    for(int i = 0; i < n; i++)
    {
        if(nodeState[i] == not_visited)
        {
            DFS(i);
        }
    }
    
    return sortedResults;
}

void topologicalSort::DFS(int start)
{
    nodeState[start] = is_visiting; 
    
    for(int n : adjacencyList[start] )
    {
        if(nodeState[n] == not_visited)
        {
            DFS(n);
        }
        if(nodeState[n] == is_visiting)
        {
            //throw error since there must be a cycle in the graph
            throw std::runtime_error("Cycle found in graph, cannot topologically sort");
        }
    }
    nodeState[start] = visited;
    sortedResults.push(vertices[start]);
}

