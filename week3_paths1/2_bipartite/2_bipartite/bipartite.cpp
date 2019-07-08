#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;


bool bipartite(vector<vector<int> > &adj){
    size_t n = adj.size();

    queue<int> q;
    vector<int> colors (n, -1);

    q.push(0);
    colors[0] = 1;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for (int i=0; i<adj[u].size(); i++){
            int v = adj[u][i];

            if(colors[v]==-1){
                colors[v] = 1 - colors[u];
                q.push(v);
            }

            else if (colors[v] == colors[u])
                return false;

        }
    }
    return true;
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
  std::cout << bipartite(adj);
}
