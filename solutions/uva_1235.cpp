#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <chrono>
#include <vector>
#include <set>
#include <queue>
#include <stdio.h>
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;



struct unionfind {
    vector<int> rank;
    vector<int> parent;

    unionfind (int size) {
        rank = vector<int>(size,0);
        parent = vector<int>(size);
        for (int i = 0 ; i < size ; i++) 
          parent[i]=i;
    }

    int find(int x) {
        int tmp = x;
        while (x != parent[x])
          x = parent[x];
        while (tmp!=x) {
            int remember = parent[tmp];
            parent[tmp]=x;
            tmp = remember;
        }
        return x;
    }

    void unite(int p, int q) {
        p = find(p);
        q = find(q);
        if (q==p) 
          return;
        if (rank[p] < rank[q])
          parent[p] = q;
        else
          parent[q] = p;
        if (rank[p] == rank[q])
          rank[p]++;
    }
};


// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (n), all nodes are between 0 and n-1.
// output: weight of a minimum spanning tree.
// time: O(ElogV).
int Kruskal(vector<iii>& edges, int n) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0;
    unionfind components(n);
    for (iii e : edges) {
        if (components.find(e.second.first) != components.find(e.second.second)) {
            mst_cost += e.first;
            components.unite(e.second.first, e.second.second);
        }
    }
    return mst_cost;
}

int calc(string a, string b){
  int sum = 0;
  for (int i = 0 ; i < 4; i ++){
    int tmp = abs(a[i] - b[i]);
    if (tmp > 5) tmp = 10 - tmp;
    sum += tmp;
  }
  return sum;
}


int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t ++){
    int N;
    cin >> N;
    int min = INF;
    vector<iii> edges;
    vector<string> passwords;

    for (int i = 0; i < N; i ++){
      string key;
      cin >> key;
      int tmp = calc("0000", key);
      if (tmp < min) min = tmp;

      for (int j = 0; j < passwords.size(); j ++){
        int w = calc(passwords[j], key);
        edges.push_back(make_pair(w, make_pair(j, i)));
        edges.push_back(make_pair(w, make_pair(i, j)));
      }
      
      passwords.push_back(key);
    }

    int ans = Kruskal(edges, N) ;
    cout << ans + min << endl;
  }
  return 0;
}
