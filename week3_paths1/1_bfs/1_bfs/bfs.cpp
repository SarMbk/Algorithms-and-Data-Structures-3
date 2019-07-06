#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  size_t n = adj.size();
  queue<int> q;
  vector<int> dist(n, -1);

  q.push(s);
  dist[s] = 0;

  while (!q.empty()){
      int u = q.front();
      q.pop();
      for (size_t i=0; i<adj[u].size(); i++){
          int v = adj[u][i];
          if(dist[v] == -1){
              q.push(v);
              dist[v] = dist[u]+1;
              if(v==t) return dist[v];
          }
      }
  }
  return -1;
}



int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
