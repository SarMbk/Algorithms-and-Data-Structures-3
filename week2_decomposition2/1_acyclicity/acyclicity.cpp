#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// These are the values with which we populate the flag vector
const int UNVISITED = -1;
const int VISITED = 0;
const int VISITED_POPPED = 1;



int hasCycle(vector<vector<int> > &adj){
    int n = adj.size();

    // Visited set
    vector<bool> visitedNodes(n, false);

    // flag[v] = -1 if the node is unvisited; 0 if visited; 1 if visited and popped
    vector<int> flag(n, UNVISITED);

    // Auxilary stack
    stack<int> s;

    s.push(0);
    visitedNodes[0] = true;
    flag[0] = VISITED;
    //cout << 0 << " ";

    while(!s.empty()){
        int p = s.top();

        // Check any adjacent nodes with flag[i] = VISITED; if yes then we have a cycle
        for (int i=0; i<adj[p].size(); i++){
            if (flag[adj[p][i]] == VISITED)
                return 1;
        }

        // Find an unvisited node an push into the stack
        bool hasAdjVertex = false;
        for (int i=0; i<adj[p].size(); i++){
            if (!visitedNodes[adj[p][i]]){
                s.push(adj[p][i]);
                visitedNodes[adj[p][i]] = true;
                flag[adj[p][i]] = VISITED;
                hasAdjVertex = true;
                //cout << adj[p][i] << " ";
                break;
            }
        }

        if (!hasAdjVertex){
            flag[p] = VISITED_POPPED;
            s.pop();
        }
    }
    //cout << endl;
    return 0;
}



int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << hasCycle(adj);
}
