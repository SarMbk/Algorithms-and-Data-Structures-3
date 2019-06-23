#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using namespace std;


// Find all nodes reachable from a given one
void exploreNode(vector<vector<int> > &adj, vector<bool> &visited, vector<int> &ccnum, int &compNum, int node) {
    visited[node] = true;
    ccnum[node] = compNum;
    for (int i=0; i<adj[node].size(); i++){
        if (!visited[adj[node][i]])
            exploreNode(adj, visited, ccnum, compNum, adj[node][i]);
    }
}


// Number all the interlinked components in the graph and return the number of components
int dfs(vector<vector<int> > &adj, vector<bool> &visited, vector<int> &ccnum) {
    int compNum = 1;
    for (int i=0; i<adj.size(); i++){
        if (!visited[i]){
            exploreNode(adj, visited, ccnum, compNum, i);
            compNum++;
        }
    }
    return compNum-1;
}


int main() {
  size_t n, m;
  std::cin >> n >> m;

  // Adjacency list
  vector<vector<int> > adj(n, vector<int>());

  // Auxilary vector to track visited nodes
  vector<bool> visited (n, false);

  // Auxilary vector to track the connected component number all initialized to -1
  vector<int> ccnum (n, -1);

  // Populate the adjacency list
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  //std::cout << number_of_components(adj);
  cout << dfs(adj, visited, ccnum);
}
