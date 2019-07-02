#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Implemented this algorithm based on CLRS ch 22.3
// These are the values with which we populate the colors vector
const int WHITE = -1;   // white = unvisited
const int GRAY = 0;     // gray = visited (in stack) but not finished
const int BLACK = 1;    // black = visited and finished (popped from stack)



// Driver function to sort the vector elements by second element of pairs in decreasing order
bool sortbysec(const pair<int,int> &a, const pair<int,int> &b) {
    return (a.second > b.second);
}




// Regular DFS implemented verbatim from CLRS
void dfs_util(vector<vector<int> > &g, vector< pair<int,int> > &postOrder, vector<int> &colors,  int &clock, int u) {
    clock++;
    colors[u] = GRAY;

    for (int i = 0; i<g[u].size(); i++){
        int v = g[u][i];
        if (colors[v] == WHITE)
            dfs_util(g, postOrder, colors, clock, v);
    }
    colors[u] = BLACK;
    clock++;
    postOrder.push_back(make_pair(u, clock));
}



void dfs_transpose_util(vector<vector<int> > &gt, vector<int> &colors, int u) {
    colors[u] = GRAY;

    for (int i = 0; i<gt[u].size(); i++){
        int v = gt[u][i];
        if (colors[v] == WHITE)
            dfs_transpose_util(gt, colors, v);
    }
    colors[u] = BLACK;
}





// DFS called on the un-transposed graph to find post order indices
void dfs(vector<vector<int> > &g, vector<pair<int, int> > &postOrder){
    int n = g.size();
    vector<int> colors(n, WHITE);

    int clock = 0;
    for (int i=0; i<n; i++){
        if (colors[i]==WHITE)
            dfs_util(g, postOrder, colors, clock, i);
    }
}





// DFS called on the transposed graph to find the number of connected components
// vertices are considered in the decreasing order of their post order indices
int dfs_transpose(vector<vector<int> > &gt, vector<pair<int, int> > &postOrder){
    int count = 0;
    int n = gt.size();
    vector<int> colors (n, WHITE);
    sort(postOrder.begin(), postOrder.end(), sortbysec);
    for (int i=0; i<n; i++){
        if (colors[postOrder[i].first] == WHITE){
            dfs_transpose_util(gt, colors, postOrder[i].first);
            count++;
        }
    }
    return count;
}




void transpose_graph(const vector<vector<int> > &g, vector<vector<int> > &gt){
    for (int i=0; i<g.size(); i++){
        for (int j = 0; j<g[i].size(); j++){
            gt[g[i][j]].push_back(i);
        }
    }
}




int connected_components(vector<vector<int> > &g){
    int n = g.size();



    // Compute the transpose
    vector<vector<int> > gt(n, vector<int>()); // transpose of graph
    transpose_graph(g, gt);

    // Vectors to store colors and post order indices of vertices
    vector<pair<int, int> > postOrder;

    // Call DFS of graph to find postOrder Indices of graph
    dfs(g, postOrder);

    // Call DFS of transpose but in main loop consider the vertices in order of decreasing post order indices
    int ans = dfs_transpose(gt, postOrder);
    return ans;



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
    std::cout << connected_components(adj);
}


























// Great algorithm explanation is available on youtube:
// https://www.youtube.com/watch?v=9esCn0awd5k&list=PLdo5W4Nhv31bK5n8-RIGhvYs8bJbgJFDR&index=27
/*
void dfs(vector<vector<int> > &adj, vector<int> &colors, int u) {
    colors[u] = GRAY;
    for (int i = 0; i<adj[u].size(); i++){
        int v = adj[u][i];
        if (colors[v] == WHITE)
            dfs(adj, colors, v);
    }
    colors[u] = BLACK;
}

// The number of strongly connected components = number of dfs calls in a graph
int connected_components(vector<vector<int> > &adj){
    int n = adj.size();
    vector<int> colors(n, WHITE);
    int count = 0;

    for (int i=0; i<n; i++){
        if (colors[i] == WHITE){
            dfs(adj, colors, i);
            count++;
        }
    }
    return count;
}

*/
