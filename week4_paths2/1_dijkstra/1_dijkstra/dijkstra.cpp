#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using namespace std;

const long infinity = 2147483647;


struct compare  {
  bool operator()(const pair<int,int> &l, const pair<int,int> &r) {
      return l.first > r.first;
  }
};


int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
    int n = adj.size();
    vector<long> dist(n, infinity);
    vector<bool> beenPopped(n, false);
    dist[s] = 0;

    // Priority queue of pairs. Key is the distance, value is the node number
    priority_queue< pair<long,int>, vector< pair<long,int> >, compare > H;
    for (int i=0; i<n; i++){
        H.push(make_pair(dist[i], i));
    }

    while (!H.empty()){
        //Keep popping until you meet the one not popped
        pair<long, int> closest = H.top();
        while(beenPopped[closest.second] && !H.empty()){
            H.pop();
            closest = H.top();
        }
        beenPopped[closest.second] = true;
        if(!H.empty()) H.pop();

        int u = closest.second;
        for (int i=0; i<adj[u].size(); i++){
            int v = adj[u][i];
            long w_uv = cost[u][i];
            if (dist[v] > dist[u] + w_uv  &&  !beenPopped[v]){
                dist[v] = dist[u] + w_uv;
                //prev[v] = u;
                H.push(make_pair(dist[v], v));
            }
        }
    }

    if (dist[t]==infinity) return -1;
    return dist[t];
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
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}
