#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;


void printGraph(vector<vector<int> > adj){
    for (int i=0; i<adj.size(); i++){
        cout << "node " << i << "  ";
        for (int j=0; j<adj[i].size(); j++)
            cout << adj[i][j] << " ";
        cout << endl;
    }
}


// This method creates the following graph
/*      0
 *     / \
 *    1   2
 *   / \ / \
 *  3   4   5
 *   \ / \ /
 *    6   7
 *     \ /
 *      8
 */
void create_graph(vector<vector<int> > &adj){
    adj.resize(9, vector<int>());

    adj[0].push_back(1);    adj[0].push_back(2);
    adj[1].push_back(0);    adj[1].push_back(3);    adj[1].push_back(4);
    adj[2].push_back(0);    adj[2].push_back(4);    adj[2].push_back(5);
    adj[3].push_back(1);    adj[3].push_back(6);
    adj[4].push_back(1);    adj[4].push_back(2);    adj[4].push_back(6);    adj[4].push_back(7);
    adj[5].push_back(2);    adj[5].push_back(7);
    adj[6].push_back(3);    adj[6].push_back(4);    adj[6].push_back(8);
    adj[7].push_back(4);    adj[7].push_back(5);    adj[7].push_back(8);
    adj[8].push_back(6);    adj[8].push_back(7);
}


// This function performs a graph bfs.
// Time complexity: O(|V| + |E|); Space complexity: O(|V|)
void bfs(vector<vector<int> > &adj){
    size_t n = adj.size();

    // Auxilary queue and vector to keep track of visited nodes
    queue<int> q;
    vector<bool> visited (n, false);

    // 1. Enqueue starting vertex and mark it as visited. In this case we start with vertex 0
    q.push(0);
    visited[0] = true;

    // 2. While there is stuff in the queue:
    // 2a.p is the front node in the queue; dequeue and print node p;
    // 2b. enqueue all vertices adjacent to p.
    while(!q.empty()){
        int p = q.front();
        q.pop();
        cout << p << " ";
        for (int i=0; i<adj[p].size(); i++){
            if (!visited[adj[p][i]]){
                q.push(adj[p][i]);
                visited[adj[p][i]] = true;
            }
        }
    }
    cout << endl;
}


// This function performs a graph dfs.
// Time complexity: O(|V| + |E|); Space complexity: O(|V|)
void dfs(vector<vector<int> > &adj){
    size_t n = adj.size();

    // Auxilary stack and vector to keep track of visited nodes
    stack<int> s;
    vector<bool> visited (n, false);

    // 1. Push starting node into a stack, mark it as visited and print it
    s.push(0);
    visited[0] = true;
    cout << 0 << " ";

    // 2. While there is stuff in the stack
    // 2a. p is the top node of the stack
    // 2b. push only one vertex adjacent to p into the stack, mark it as visited and print it
    // 2c. if p has no unvisited adjacent vertices, then pop top element from the stack
    while (!s.empty()){
        int p = s.top();
        bool hasValAdjVertex = false;
        for (int i=0; i<adj[p].size(); i++){
            if (!visited[adj[p][i]]){
                s.push(adj[p][i]);
                visited[adj[p][i]] = true;
                cout << adj[p][i] << " ";
                hasValAdjVertex = true;
                break;
            }
        }
        if (!hasValAdjVertex) s.pop();
    }
    cout << endl;
}


int main() {
    // adjacency list
    vector<vector<int> > adj;

    // populate the graph
    create_graph(adj);

    // Print graph (duh)
    printGraph(adj);

    // Perform a bfs
    bfs(adj);

    // Perform a dfs
    dfs(adj);
}
