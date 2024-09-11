Problem statement
Given a graph with 'V' vertices numbered from 0 to 'V' - 1 and 'E' edges. Determine if it is a tree or not?

Detailed explanation ( Input/output format, Notes, Images )
Constraints :
1 < 'V' <= 10^5
0 <= 'E' <= min(10^5, V*(V-1)/2)
0 <= u, v <= V-1

Time Limit: 1 sec
Sample Input 1:
3 2
0 1
1 2
Sample Output 1:
True
Explanation of Sample Input 1:
We clearly can see that it is a tree since it satisfies the property of a tree.
  
  https://files.codingninjas.in/0000000000004469.JPG


Sample Input 2:
3 3
0 1
1 2
0 2
Sample Output 2:
False
Explanation of Sample Input 2:
As we can see that it is not a tree since it doesn't satisfy the property of a tree.

 https://files.codingninjas.in/0000000000004468.JPG 




Solution:

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to check if the graph is a tree
bool isTree(vector<vector<int>>& adj, int V) {
    // A tree must have exactly V - 1 edges
    int E = 0;
    for (int i = 0; i < V; ++i) {
        E += adj[i].size();
    }
    E /= 2; // Since each edge is counted twice in an undirected graph
    
    if (E != V - 1) {
        return false;
    }

    // Vector to keep track of visited vertices
    vector<bool> visited(V, false);
    
    // Perform BFS or DFS to check if the graph is connected and acyclic
    queue<int> q;
    q.push(0); // Start BFS from vertex 0
    visited[0] = true;
    int visitedCount = 1; // To count the number of visited vertices
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        // Explore all neighbors of the current node
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                visitedCount++;
                q.push(neighbor);
            }
        }
    }
    
    // Check if we visited all vertices
    if (visitedCount != V) {
        return false;
    }

    return true; // If all checks pass, it's a tree
}

int main() {
    int V, E;
    cin >> V >> E; // Number of vertices and edges
    
    // Adjacency list to store the graph
    vector<vector<int>> adj(V);
    
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v; // Input each edge
        adj[u].push_back(v);
        adj[v].push_back(u); // Since the graph is undirected
    }
    
    // Check if the graph is a tree
    if (isTree(adj, V)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    
    return 0;
}
