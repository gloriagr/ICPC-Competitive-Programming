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
typedef long long ll;

const int INF = 1e9;

int main(){
    int n;
    cin >> n;
    vector<ll> ans;
    ans.push_back(1);
    ans.push_back(1);
    ans.push_back(1);
    for (int i = 3; i < 62; i++){
      ans.push_back(ans[i-1]+ans[i-2]+ans[i-3]);
    }
    int idx = 1;
    while(n > 0){
      cout << "Case " << idx++ << ": " << ans[n-1] << endl;
      cin >> n;
    }
}
