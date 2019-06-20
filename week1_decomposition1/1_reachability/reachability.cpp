#include <iostream>
#include <vector>
using namespace std;

using std::vector;
using std::pair;



void reachInternal(vector<vector<int> > &adj, int x, int y, vector<bool> &visited) {
    visited[x] = true;
    for (int i=0; i<adj[x].size(); i++){
        if (!visited[adj[x][i]])
            reachInternal(adj, adj[x][i], y, visited);
    }
}

int reach(vector<vector<int> > &adj, int x, int y, vector<bool> &visited){
    reachInternal(adj, x, y, visited);
    return visited[y];
}

void printGraph(vector<vector<int> > adj){
    for (int i=0; i<adj.size(); i++){
        cout << "node " << i+1 << "  ";
        for (int j=0; j<adj[i].size(); j++)
            cout << adj[i][j] + 1 << " ";
        cout << endl;
    }
}


int main() {
  size_t n, m;
  std::cin >> n >> m;

  // adjacency list
  vector<vector<int> > adj(n, vector<int>());

  // auxilary vector to keep track of visited nodes
  vector<bool> visited (n, false);

  // populate the adjacency lists
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  // determine reachability
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1, visited);
}
