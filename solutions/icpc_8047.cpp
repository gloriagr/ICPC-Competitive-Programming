// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli.
// Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

/*
 * Input graphs should be represented as an adjacency list
 * where the nodes are named 0,1,...,|V|-1.
 * If g is unweighted (type vvi), g[u] contains the neighbors of u
 * If g is weighted (type vvii), g[u] contains pairs (v,w) such that u->v has weight w
 */

/********** topological sort **********/

// input: a graph (g)
// output: is g a DAG (return value), a topological ordering of g (order)
// comment: order is valid only if g is a DAG
bool topological_sort(const vvi& g, vi& order) {
    // compute indegree of all nodes
    vi indegree (g.size(), 0);
    for (int v=0; v<g.size(); v++) for (int u : g[v]) indegree[u]++;
    // order sources first
    order = vector<int>();
    for (int v=0; v<g.size(); v++) if (indegree[v] == 0) order.push_back(v);
    // go over the ordered nodes and remove outgoing edges,
    // add new sources to the ordering
    for (int i=0; i<order.size(); i++) for (int u : g[order[i]]) {
        indegree[u]--;
        if (indegree[u]==0) order.push_back(u);
    }
    return order.size()==g.size();
}

/********** strongly connected components **********/

const int UNSEEN = -1;
const int SEEN = 1;

// DFS on digraph g from node u:
// visit a node only if it is mapped to the color UNSEEN,
// Mark all visited nodes in the color map using the given color.
// input: digraph (g), node (v), mapping:node->color (colorMap), color (color).
// output: DFS post-order (S), node coloring (colorMap).
void KosarajuDFS(const vvi& g, int u, vi& S, vi& colorMap, int color) {
    colorMap[u] = color;
    for (auto& v : g[u])
        if (colorMap[v] == UNSEEN)
            KosarajuDFS(g, v, S, colorMap, color);
    S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs
// input: directed graph (g)
// output: the number of SCCs (return value), a mapping from node to SCC color (components)
int findSCC(const vvi& g, vi& components) {
    // first pass: record the `post-order' of original graph
    vi postOrder, seen;
    seen.assign(g.size(), UNSEEN);
    for (int i = 0; i < g.size(); ++i)
        if (seen[i] == UNSEEN)
            KosarajuDFS(g, i, postOrder, seen, SEEN);
    // second pass: explore the SCCs based on first pass result
    vvi reverse_g(g.size(),vi());
    for (int u=0; u<g.size(); u++) for (int v : g[u]) reverse_g[v].push_back(u);
    vi dummy;
    components.assign(g.size(), UNSEEN);
    int numSCC = 0;
    for (int i = (int)g.size()-1; i >= 0; --i)
        if (components[postOrder[i]] == UNSEEN)
            KosarajuDFS(reverse_g, postOrder[i], dummy, components, numSCC++);
    return numSCC;
}

// Computes the SCC graph of a given digraph
// input: directed graph (g)
// output: strongly connected components graph of g (sccg)
void findSCCgraph(const vvi& g, vsi& sccg) {
    vi component;
    int n = findSCC(g, component);
    sccg.assign(n, si());
    for (int u=0; u<g.size(); u++) for (int v: g[u]) // for every edge u->v
        if (component[u] != component[v])
            sccg[component[u]].insert(component[v]);
}

/********** Dijkstra **********/

// input: digraph (g), source (s)
// output: distances from s (dist)
void Dijkstra(const vector<vii>& g, int s, vi& dist) {
    dist = vi(g.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top(); q.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (ii next : g[u]) {
            int v = next.first, w = next.second;
            if (dist[u]+w < dist[v]) {
                dist[v] = dist[u]+w;
                q.push({dist[v], v});
            }
        }
    }
}

/********** Bellman-Ford **********/

// input: weighted directed graph (g), source node (s)
// output: is there a negative cycle in g? (return value), the distances from s (d)
// comment: the values in d are valid only if there is no negative cycle
bool BellmanFord(const vvii& g, int s, vi& d) {
    d.assign(g.size(), INF);
    d[s] = 0;
    bool changed = false;
    // V times
    for (int i = 0; i < g.size(); ++i) {
        changed = false;
        // go over all edges u->v with weight w
        for (int u = 0; u < g.size(); ++u) for (ii e : g[u]) {
            int v = e.first;
            int w = e.second;
            // relax the edge
            if (d[u] < INF && d[u]+w < d[v]) {
                d[v] = d[u]+w;
                changed = true;
            }
        }
    }
    // there is a negative cycle if there were changes in the last iteration
    return changed;
}

/********** Floyd-Warshall **********/

// input: weighted directed graph (g)
// output: the pairwise distances (d)
void FloydWarshall(const vvii& g, vvi& d) {
    // initialize distances according to the graph edges
    d.assign(g.size(), vi(g.size(), INF));
    for (int u=0; u<g.size(); ++u) d[u][u] = 0;
    for (int u=0; u<g.size(); ++u) for (ii e: g[u]) {
        int v = e.first; int w = e.second;
        d[u][v] = min(d[u][v],w);
    }
    // relax distances using the Floyd-Warshall algorithm
    for (int k=0; k<g.size(); ++k)
        for (int u=0; u<g.size(); ++u)
            for (int v=0; v<g.size(); ++v)
                d[u][v] = min(d[u][v], d[u][k]+d[k][v]);
}

void print_mat(vvii &mat){
  int idx = 0;
  cout << "size " << mat.size() << endl;
  for (vii row : mat){
    cout << idx++ << ":";
    for (ii x : row){
      cout << x.first << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void print_dists(vvi d){
  for (int i = 0; i < d.size(); i++){
    for (int j = 0; j < d[i].size(); j++){
      cout << "dist " << i << " " << j << " is " << d[i][j] << endl;
    }
  }
}

int main() {
  int n, m;
  while(cin >> m >> n) {
    vvii g;
    for (int i = 0; i < 26; i ++) {
      vii tmp;
      g.push_back(tmp);
    }

    for (int i = 0; i < m; i ++) {
      char a, b;
      cin >> a >> b;
      g[a-'a'].push_back(make_pair(b-'a', 1));
    }

    vvi d;
    FloydWarshall(g, d);
    for (int i = 0; i < n; i++){
      string a, b;
      cin >> a >> b;
      if (a.size() != b.size()){
        cout << "no" << endl;
        continue;
      }
      
      int j;
      for (j = 0; j < a.size(); j++){
        if (d[a[j] - 'a'][b[j] - 'a'] == INF){
          cout << "no" << endl;
          break;
        }
      }

      if (j == a.size()){
        cout << "yes" << endl;
      }
    }
  }

  return 0;
}
