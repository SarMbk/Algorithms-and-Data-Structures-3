#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

//const long long infinity = 1000000000000000;
const long long infinity = std::numeric_limits<long long>::max();



bool overflow(long long du, long long wuv){
    if (du > 0 && wuv > 0){
        if (du + wuv < 0) return true;
        else return false;
    }

    if (du < 0 && wuv < 0){
        if (du + wuv > 0) return true;
        else return false;
    }
}


void BellmanFord2(vector< vector<int> > &adj, vector< vector<int> > & cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> & shortest){
    int n = adj.size();
    distance[s] = 0;
    reachable[s] = 1;
    queue<int> q;

    // Determine distances, place all nodes relaxed on nth iteration into the queue
    for(int k=0; k < n; k++){
        for(int u = 0; u < n; u++){
            for (int i=0; i< adj[u].size(); i++){
                int v = adj[u][i];
                long long w_uv = cost[u][i];
                //if(distance[u] != std::numeric_limits<int>::max() && distance[v] > distance[u] + w_uv){
                //if (distance[v] - distance[u] > w_uv){
                //if(distance[u] != infinity && distance[v] > distance[u] + w_uv){
                if(!overflow(distance[u], w_uv) && distance[v] > distance[u] + w_uv){
                    distance[v] = distance[u] + w_uv;
                    reachable[v] = 1;
                    if (k==n-1) q.push(v);
                }
                else if (overflow(distance[u], w_uv) && w_uv > 0 && distance[u] > 0){
                    distance[v] = infinity;
                }
                else if (overflow(distance[u], w_uv) && w_uv <0 && distance[u] <0){
                    distance[v] = -infinity;
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
        visited[u] = 1;
        if (u != s) shortest[u] = 0;
        for (int i =0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(!visited[v]){
                q.push(v);
                visited[v] = 1;
                shortest[v] = 0;
                reachable[v] = 1;
            }
        }
    }


//    for (int i = 0; i < distance.size(); i++){
//        if (distance[i] != std::numeric_limits<long long>::max()){
//            reachable[i] = 1;
//        }
//    }
}














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
    //vector<long long> distance(n, std::numeric_limits<long long>::max());
    vector<long long> distance(n, infinity);
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    //shortest_paths(adj, cost, s, distance, reachable, shortest);
    BellmanFord2(adj, cost, s, distance, reachable, shortest);

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









void BellmanFord(vector< vector<int> > &adj, vector< vector<int> > & cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> & shortest){
    int n = adj.size();
    distance[s] = 0;

    // Determine distances
    for(int k=0; k < n-1; k++){
        for(int u = 0; u < n; u++){
            //if (u==s) continue;
            for (int i=0; i< adj[u].size(); i++){
                int v = adj[u][i];
                long long w_uv = cost[u][i];
                //if(distance[v] > distance[u] + w_uv){
                if (distance[v] - distance[u] > w_uv){
                    distance[v] = distance[u] + w_uv;
                    reachable[v] = 1;
                }
            }
        }
    }


    // Determine presence of negative cycles
    for (int k = 0; k < n-1; k++){
        for (int u = 0; u < n; u++){
            for (int i = 0; i < adj[u].size(); i++){
                int v = adj[u][i];
                long long w_uv = cost[u][i];
                //if (distance[v] > distance[u] + w_uv){
                if (distance[v] - distance[u] > w_uv){
                    distance[v] = distance[u] + w_uv;
                    shortest[v] = 0;
                }
            }
        }
    }

    for (int i = 0; i < distance.size(); i++){
        //if (distance[i] != std::numeric_limits<long long>::max())
        if (distance[i] != infinity)
            reachable[i] = 1;
    }
}













void sp(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
    //write your code here
    reachable[s] = 1;
    distance[s] = 0;
    queue<int> q;
    int n = adj.size();

    for (int k = 0; k < n; k++) {
        for (int u = 0; u < n; u++){
            for (int i = 0; i < n; i++) {
                int v = adj[u][i];
                int w_uv = cost[u][i];
                if (distance[u]!= std::numeric_limits<long long>::max() && distance[v] > distance[u] + w_uv) {
                    distance[v] = distance[u] + w_uv;
                    reachable[v] = 1;
                    if (k == n - 1) {
                        q.push(v);
                    }
                }
            }
        }
    }

    vector<int> visited(n);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        visited[u] = 1;
        if(u != s) shortest[u] = 0;
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                q.push(v);
                visited[v] = 1;
                shortest[v] = 0;
            }
        }
    }
    distance[s] = 0;
}
