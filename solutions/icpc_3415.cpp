#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <string>

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

typedef struct student {
    int height;
    char sex;
    string music;
    string sport;
} student ;

/********** Max Flow **********/


int augment(vvi& res, int s, int t, const vi& p, int minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
        res[p[t]][t] -= f;
        res[t][p[t]] += f;
        return f;
    }
    return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp (int n, vector<iii>& edges, int s, int t) {
    // initialise adjacenty list and residuals adjacency matrix
    vvi res(n,vi(n,0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
        }
        // add flow on the path between s to t according to p
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}


int main() {
    int tests;
    cin >> tests;
    while(tests--) {
        vector<student> students;
        vector<iii> graph;
        int n;
        cin >> n;
        for(int i = 0 ; i < n ; i++) {
            student s;
            cin >> s.height >> s.sex >> s.music >> s.sport;
            students.push_back(s);
        }
        for(int i = 0 ; i < n ; i++) {
            student s1 = students[i];
            if(s1.sex == 'M') {
                for(int j = 0; j < n ; j++) {
                    student s2 = students[j];
                    if(j != i && \
                    (s1.sex != s2.sex && abs(s1.height - s2.height) <= 40 && s1.music == s2.music && s1.sport != s2.sport)) {
                        graph.push_back(make_pair(1,make_pair(i+1,j+1)));
                    }
                }
            }
        }
        for(int i = 0 ; i < n ; i++) {
            if(students[i].sex == 'M') graph.push_back(make_pair(1,make_pair(0,i+1)));
            if(students[i].sex == 'F') graph.push_back(make_pair(1,make_pair(i+1,n+1)));
        }

        int res = EdmondsKarp(n+2,graph,0,n+1);
        cout << n - res << endl;
    }
    return 0;
}