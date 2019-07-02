#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Implemented this algorithm based on CLRS ch 22. See CLRS book for more info.
// Personal note: it's kind of a long winded solution. I wonder if there is a shorter and a more eloquent one.


// // // CONSTANTS // // //

// These are the values with which we populate the colors vectors while performing dfs
const int WHITE = -1;   // white = unvisited
const int GRAY = 0;     // gray = visited (in stack) but not finished
const int BLACK = 1;    // black = visited and finished (popped from stack)



// // // FUNCTION PROTOTYPES // // //

bool sortbysec(const pair<int,int> &a, const pair<int,int> &b);
void dfs(const vector<vector<int> > &g, vector<pair<int, int> > &postOrder);
void dfs_util(const vector<vector<int> > &g, vector<pair<int, int> > &postOrder, vector<int> &colors, int &clock, int u);
int dfs_transpose(const vector<vector<int> > &gt, vector<pair<int, int> > &postOrder);
void dfs_transpose_util(const vector<vector<int> > &gt, vector<int> &colors, int u);
void transpose_graph(const vector<vector<int> > &g, vector<vector<int> > &gt);
int connected_components(const vector<vector<int> > &g);



// // // MAIN FUNCTION // // //

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



// // // FUNCTION DEFINITIONS // // //


// function that helps to make the transposed graph.
void transpose_graph(const vector<vector<int> > &g, vector<vector<int> > &gt){
    for (int i=0; i<g.size(); i++){
        for (int j = 0; j<g[i].size(); j++){
            gt[g[i][j]].push_back(i);
        }
    }
}


// DFS run on an un-transposed graph in order to find indices of post-order traversal
// Post order (aka finishing times) indices are stored in a vector of pairs (deliberately not in just a vector of ints)
// This is because the function connected-components will then run dfs_transpose
// which is a similar algorithm except it considers vertices in the decreasing order of their finishing times
// Therefore, to make it possible to run dfs on vertices in the decreasing order of finishing times, we had to store those
// finishing times in a vector of pairs<int, int>
// First value in pair = vertex number
// Second value in pair = post order index (aka finishing time)
void dfs(const vector<vector<int> > &g, vector<pair<int, int> > &postOrder){
    int n = g.size();
    vector<int> colors(n, WHITE);

    int clock = 0;
    for (int i=0; i<n; i++){
        if (colors[i]==WHITE)
            dfs_util(g, postOrder, colors, clock, i);
    }
}


// Utility function supporting dfs;
// g = graph represented as a nested adjacency vector
// postOrder = vector storing each vertex's finishing time. postOrder[i].first = vertex number. postOrder[i].second = finishing time
// colors = vector of WHITE = -1; GRAY = 0; BLACK = 1. To help keep track of visited nodes.
void dfs_util(const vector<vector<int> > &g, vector< pair<int,int> > &postOrder, vector<int> &colors,  int &clock, int u) {
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


// Driver function to sort the vector elements by second element of pairs in decreasing order
bool sortbysec(const pair<int,int> &a, const pair<int,int> &b) {
    return (a.second > b.second);
}


// Modified DFS that considers vertices in the decreasing order of their finishing times
// Finishing times of the un-transposed graph were found using the regular dfs function
// gt = transposed graph represented as a nested adjacency vector
int dfs_transpose(const vector<vector<int> > &gt, vector<pair<int, int> > &postOrder){
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


// Utility function supporting dfs_transpose
void dfs_transpose_util(const vector<vector<int> > &gt, vector<int> &colors, int u) {
    colors[u] = GRAY;

    for (int i = 0; i<gt[u].size(); i++){
        int v = gt[u][i];
        if (colors[v] == WHITE)
            dfs_transpose_util(gt, colors, v);
    }
    colors[u] = BLACK;
}


// Function that returns the number of connected components of a given graph in O(|V|+|E|) using O(|V|+|E|) auxilary space.
int connected_components(const vector<vector<int> > &g){
    int n = g.size();

    // Compute the transpose
    vector<vector<int> > gt(n, vector<int>()); // transpose of graph
    transpose_graph(g, gt);

    // Vector to store post-order indices of vertices
    vector<pair<int, int> > postOrder;

    // Call DFS of graph to find post-order indices of graph
    dfs(g, postOrder);

    // Call DFS of transpose but in main loop consider the vertices in order of decreasing post order indices,
    // count how many times you call dfs, that's the number of strongly connected components
    int ans = dfs_transpose(gt, postOrder);
    return ans;
}
