#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// These are the values with which we populate the colors vector
const int WHITE = -1;   // white = unvisited
const int GRAY = 0;     // gray = visited (in stack) but not finished
const int BLACK = 1;    // black = visited and finished (popped from stack)


bool hasCycleUtil(vector<vector<int> > &adj, int u, vector<int> &colors){
    colors[u] = GRAY;
    for (int i=0; i<adj[u].size(); i++){
        int v = adj[u][i];
        if (colors[v] == GRAY)
            return true;
        if (colors[v] == WHITE && hasCycleUtil(adj, v, colors))
            return true;
    }
    colors[u] = BLACK;
    return false;
}


bool hasCycle(vector<vector<int> > &adj){
    int n = adj.size();
    vector<int> colors(n, WHITE);

    for (int i=0; i<n; i++){
        if (colors[i] == WHITE)
            if (hasCycleUtil(adj, i, colors) == true)
                return true;
    }

    return false;
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
