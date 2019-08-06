#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;


const long long infinity = std::numeric_limits<long long>::max();


void ShortestPaths(vector< vector<int> > &adj, vector< vector<int> > & cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> & shortest);


int main() {
    int n, m, s;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, infinity);
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    ShortestPaths(adj, cost, s, distance, reachable, shortest);

    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
          std::cout << "*\n";
        }
        else if (!shortest[i]) {
          std::cout << "-\n";
        }
        else {
          std::cout << distance[i] << "\n";
        }
    }
}



void ShortestPaths(vector< vector<int> > &adj, vector< vector<int> > & cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> & shortest){
    int n = adj.size();
    distance[s] = 0;
    reachable[s] = 1;
    queue<int> q;

    // Determine distances using Bellman Ford, place all nodes relaxed on nth iteration into the queue because those are ones reachable via with neg cycles
    for(int k=0; k < n; k++){
        for(int u = 0; u < n; u++){
            for (int i=0; i< adj[u].size(); i++){
                int v = adj[u][i];
                long long w_uv = cost[u][i];

                if(distance[v] > distance[u] + w_uv && distance[u] != infinity){
                    distance[v] = distance[u] + w_uv;
                    reachable[v] = 1;
                    if (k==n-1){
                        shortest[v] = 0;
                        q.push(v);
                    }
                }
            }
        }
    }


    // Determine nodes that are reachable from end nodes that were pushed in the queue during the nth relaxation.
    // Nodes reachable from that set all have negative weight cycles. Use BFS to find those nodes
    vector<int> visited (n, 0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for (int i =0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(!visited[v]){
                q.push(v);
                visited[v] = 1;
                shortest[v] = 0;
            }
        }
    }

}
















