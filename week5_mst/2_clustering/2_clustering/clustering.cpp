#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <set>
#include <cassert>
using namespace std;


// Disjoint set data structure
class disjointSet{
    unordered_map<int, int> parent;
    int numSets = 0;

public:
    int GetNumSets(){
        return numSets;
    }

    void MakeSet(vector<int> const &points){
        for (int i=0; i<points.size(); i++){
            parent[i] = i;
            numSets++;
        }
    }

    int Find(int point){
      if(parent[point] == point)
          return point;
      return Find(parent[point]);
    }

    void Union(int pointA, int pointB){
        int setA = Find(pointA);
        int setB = Find(pointB);
        parent[setA] = setB;
        numSets--;
    }
};


struct edge{
    int u, v;
    double d;
};


// functor to help sort vector of edges
bool sortByEdge(const edge* e1, const edge* e2){
    return e1->d < e2->d;
}


// Calculate lenghts of all possible edges given the node coordinates
void calcAllEdges(vector<edge*> &allEdges, vector<int> const &x, vector<int> const &y){
    int n = x.size();
    for (int i = 0; i<n; i++){
        for (int j = i+1; j<n; j++){
            double x1 = x[i], y1 = y[i];
            double x2 = x[j], y2 = y[j];
            double d = sqrt(pow((x2-x1),2) + pow((y2-y1), 2));
            edge* e = new edge;
            e->u = i;
            e->v= j;
            e->d = d;
            allEdges.push_back(e);
        }
    }
}


// Problem solution which is an adaptation of the Kruskal's algorithm
double clustering(vector<int> x, vector<int> y, int k) {

    int n = x.size();       // number of nodes
    double result = 0.;     // total weight of the min. spanning tree

    // Calc all possible edge weights and sort all edges
    vector<edge*> allEdges;
    calcAllEdges(allEdges, x, y);
    sort(allEdges.begin(), allEdges.end(), sortByEdge);

    // Begin Kruskal's algo
    set<edge*> A;
    disjointSet ds;
    ds.MakeSet(x);

    for (int i=0; i < allEdges.size(); i++){
        if ( ds.Find(allEdges[i]->u) != ds.Find(allEdges[i]->v) ){
            A.insert(allEdges[i]);
            ds.Union(allEdges[i]->u, allEdges[i]->v);
            if (ds.GetNumSets()==k-1)
                return allEdges[i]->d;
        }
    }

    return -1.;
}



int main() {
    size_t n;
    int k;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cin >> k;
    std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
