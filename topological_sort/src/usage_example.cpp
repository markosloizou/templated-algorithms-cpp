#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <string> 

#include "templated_topological_sort.h"
#include "templated_topological_sort.cpp"

using namespace std;

int main()
{
    
    /*Performing topological Sort on a graph with integers as node data */
    // no cycles are found in this graph
    vector<int> vertices{0,1,2,3,4,5,6,7,8};
    
    vector<pair<int,int>> edges {
    {0,1},
    {1,2},
    {3,2},
    {3,4},
    {4,5},
    {2,5},
    {0,6},
    {1,6},
    {7,6},
    };
    
    topologicalSort ts(vertices,edges);
    stack<int> resultStack = ts.sort();
    
    
    while(!resultStack.empty())
    {
        cout << ' ' << resultStack.top();
        resultStack.pop();
    }
    
    cout << endl;
    
    
    /* Doubles used with a cycle in the graph */
    /* 0 -> 1 -> 2 -> 0 */ 
    vector<double> vertices2{0.0,1.0,2.0};
    vector<pair<double,double>> edges2 {
    {0.0,1.0},
    {1.0,2.0},
    {2.0,0.0}
    };
    
    topologicalSort ts2(vertices2,edges2);
    
    //Topological sort throws a runtime exception when a cycle is found
    try{
        stack<double> resultStackD = ts2.sort();
        
        while(!resultStack.empty())
        {
            cout << ' ' << resultStack.top();
            resultStack.pop();
        }
        
        cout << endl;
    } catch(runtime_error)
    {
        cout << "Cycle found, cannot sort" << endl;
    }
    
    
    
    
    /* Final example with strings */ 
    vector<string> nodesS = {"undershorts", "pants", "belt", "shirt", "tie", "jacket", "shoes", "socks", "watch"};
    
    vector<pair<string,string>> edgesS = {
    {"undershorts", "shoes"},
    {"undershorts", "pants"},
    {"pants", "belt"},
    {"belt", "jacket"},
    {"shirt", "belt"},
    {"shirt", "tie"},
    {"tie", "jacket"},
    {"pants", "shoes"},
    {"socks", "shoes"}
    };
    
    topologicalSort tsS(nodesS, edgesS);
    stack<string> resultStackS;
    
    try{
        resultStackS = tsS.sort();
        
        while(!resultStackS.empty())
        {
            cout << ' ' << resultStackS.top();
            resultStackS.pop();
        }
        
        cout << endl;
    } catch(runtime_error)
    {
        cout << "Cycle found, cannot sort" << endl;
    }
    
    return 0;
}
