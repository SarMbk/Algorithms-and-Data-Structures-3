#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <queue>
using namespace std;

using std::vector;
using std::pair;

int acyclic(vector<vector<int> > &adj) {
  //write your code here
  return 0;
}



int hasCycle(vector<vector<int> > &adj){
    size_t n = adj.size();

    // Auxilary stack and vector to keep track of visited nodes
    stack<int> s;
    vector<bool> visited (n, false);
    unordered_map <int,int> m;
    for (int i=0; i<n; i++)
        m.emplace(i,0);

    s.push(0);
    visited[0] = true;
    cout << 0 << " ";


    while (!s.empty()){
        int p = s.top();
        m[p]++;
        if (m[p]>1) return 1;
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
    return 0;
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
//  std::cout << acyclic(adj);
  cout << "ans :" << hasCycle(adj) << endl;
}
