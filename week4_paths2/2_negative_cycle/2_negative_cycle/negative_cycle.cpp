#include <iostream>
#include <vector>
using std::vector;


const long long int infinity =  2147483647;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
    int n = adj.size();
    vector<long long int> dist(n, infinity);
    dist[0] = 0;

    for (int k = 0; k < n-1; k++){
        for (int u=0; u<n; u++){
            for (size_t i = 0; i < adj[u].size(); i++){
                int v = adj[u][i];
                long long int w_uv = cost[u][i];
                if (dist[v] > dist[u] + w_uv){
                    dist[v] = dist[u] + w_uv;
                }
            }
        }
    }

    for (int u = 0; u<n; u++){
        for (size_t i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            long long int w_uv = cost[u][i];
            if (dist[v] > dist[u] + w_uv)
                return 1;
        }
    }

    return 0;
}



int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost);
}
