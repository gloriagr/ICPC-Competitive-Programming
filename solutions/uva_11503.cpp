#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct unionfind
{
    vector<int> rank;
    vector<int> parent;
    vector<int> group_size;

    unionfind(int size) {
        rank = vector<int>(size,0);
        group_size = vector<int>(size,1);
        parent = vector<int>(size);
        for (int i = 0; i < size ; i++)
            parent[i] = i;
    }

    int find(int x) {
        int tmp = x;
        while (x != parent[x]) 
            x = parent[x];
        while(tmp != x) {//for log*, not needed most of the time
            int remember = parent[tmp];
            parent[tmp] = x;
            tmp=remember;
        }
        return x;
    }

    int Union(int p, int q) {
        p = find(p);
        q = find(q);
        if(q == p) {
            //alredy in the same group
            return group_size[p];
        }

        int ret = 0;
        if(rank[p] < rank[q]) {
            parent[p] = q;
            group_size[q] += group_size[p];
            ret = group_size[q];
        } else {
            parent[q] = p;
            group_size[p] += group_size[q];
            ret = group_size[p];
        }
        if(rank[p] == rank[q])
            rank[p]++;

        return ret;
    }
};

 int main() {
     int tests = 0;
     cin >> tests;
     for(int i = 0 ; i < tests ; i++) {
         int friendships = 0;
         cin >> friendships; //<= 100,000
         unionfind uf = unionfind(2*friendships);
         map<string,int> m;
         int friends = 0;
         for(int j = 0 ; j < friendships ; j++) { //O(100,000) O(n)
             string f1, f2;
             cin >> f1 >> f2;
             if(m.find(f1) == m.end()) m[f1] = ++friends;  //O(log(100,000)) O(logn)
             if(m.find(f2) == m.end()) m[f2] = ++friends;
              //O(log*n)
             cout << uf.Union(m[f1],m[f2]) << endl;
         }
     }
    return 0;
}