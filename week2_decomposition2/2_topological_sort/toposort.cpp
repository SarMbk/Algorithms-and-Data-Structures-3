#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


// Implemented this algorithm based on CLRS ch 22.3
// These are the values with which we populate the colors vector
const int WHITE = -1;   // white = unvisited
const int GRAY = 0;     // gray = visited (in stack) but not finished
const int BLACK = 1;    // black = visited and finished (popped from stack)


// Regular DFS without toposort feature implemented verbatim from CLRS
// Note that it has attributes that are not necessary for this assignment
// e.g. postOrder, preOrder, time.
// This algorithm is included here just for my own reference. Not used for the solution
void dfs_util(vector<vector<int> > &adj, vector<int> &preOrder, vector<int> &postOrder, vector<int> &colors,  int &time, int u) {
    time++;
    preOrder[u] = time;
    colors[u] = GRAY;

    for (int i = 0; i<adj[u].size(); i++){
        int v = adj[u][i];
        if (colors[v] == WHITE)
            dfs_util(adj, preOrder, postOrder, colors, time, v);
    }
    colors[u] = BLACK;
    time++;
    postOrder[u] = time;
}

void dfs(vector<vector<int> > &adj){
    int n = adj.size();
    vector<int> colors(n, WHITE);
    vector<int> preOrder(n, -1);
    vector<int> postOrder(n, -1);
    int time = 0;
    for (int i=0; i<n; i++){
        if (colors[i]==WHITE)
            dfs_util(adj, preOrder, postOrder, colors, time, i);
    }
}


// DFS modified to return a topologically sorted vector.
// The algorithm dfs (written out above) was modified, attributes not needed for this problem removed
void dfs_visit_topo(vector<vector<int> > &adj, vector<int> &colors, vector<int> &topoOrder, int u) {
    colors[u] = GRAY;
    for (int i = 0; i<adj[u].size(); i++){
        int v = adj[u][i];
        if (colors[v] == WHITE)
            dfs_visit_topo(adj, colors, topoOrder, v);
    }
    colors[u] = BLACK;
    topoOrder.push_back(u);
}

vector<int> dfs_topo(vector<vector<int> > &adj){
    int n = adj.size();
    vector<int> colors(n, WHITE);
    vector<int> topoOrder;

    for (int i=0; i<n; i++){
        if (colors[i]==WHITE)
            dfs_visit_topo(adj, colors, topoOrder, i);
    }
    reverse(topoOrder.begin(), topoOrder.end());
    return topoOrder;
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
    vector<int> order = dfs_topo(adj);
    for (size_t i = 0; i < order.size(); i++) {
        std::cout << order[i] + 1 << " ";
    }
}
