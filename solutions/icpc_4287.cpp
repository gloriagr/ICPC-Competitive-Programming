#include <utility>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <set>
#include <functional>
#include <vector>
#include <algorithm>

#define ll long long



using namespace std;

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

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
int findSCCgraph(const vvi& g, vsi& sccg) {
    vi component;
    int n = findSCC(g, component);
    sccg.assign(n, si());
    for (int u=0; u<g.size(); u++) for (int v: g[u]) {// for every edge u->v
            if (component[u] != component[v]) {
                sccg[component[u]].insert(component[v]);
            }
    }
    return n;
}

int main(){
    int cases;
    cin >> cases;
    for (int t = 0; t < cases; t++){
        int n,m;
        cin >> n >> m;
        vvi graph;
        for (int i = 0; i < n; i ++){
            vi tmp;
            graph.push_back(tmp);
        }
        for (int i = 0; i < m; i ++){
            int a, b;
            cin >> a >> b;
            graph[a-1].push_back(b-1);
        }

        vsi sccGraph;
        int size = findSCCgraph(graph, sccGraph);

        vsi reverse_sccg;
        for(int i = 0 ; i < sccGraph.size() ; i++) {
            si tmp;
            reverse_sccg.push_back(tmp);
        }
        for (int u = 0; u < sccGraph.size(); u++) {
            for (int v : sccGraph[u]) {
                reverse_sccg[v].insert(u);
            }
        }

        int sinks = 0 , sources = 0;
        for(int i = 0 ; i < sccGraph.size() && m > 0 ; i++) {
            bool sink = true;
            bool source = true;
            if(!sccGraph[i].empty()) sink = false;
            if(!reverse_sccg[i].empty()) source = false;
            if(sink) sinks++;
            if(source) sources++;
        }
        long long res = max(sinks, sources);
        if(m == 0) res = n;
        if(sccGraph.size() == 1) res = 0;
        cout << res << endl;
    }
    return 0;
}
