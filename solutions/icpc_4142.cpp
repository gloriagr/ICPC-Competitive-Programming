/* PARADIGM - Brute Force (input is small enough) */

#include <utility>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <functional>
#include <vector>

#define ll long long

using namespace std;

class Node{
  
    public:
      string name;
      ll min;
      ll max;

      Node(string name1, ll min1, ll max1){
        name = name1;
        min = min1;
        max = max1;
      }
};

int main(){
  int cases;
  cin >> cases;
  for (int j = 0; j< cases; j++){
    int db;
    cin >> db;
    vector<Node> dbs;
    for (int i = 0; i < db; i++){
      string n;
      ll mi,ma;
      cin >> n >> mi >> ma;
      dbs.push_back(Node(n, mi, ma));
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
      ll price;
      cin >> price;
      string ans = "UNDETERMINED";
      for (int i = 0; i < db; i ++){
        if (dbs[i].min <= price && dbs[i].max >= price){
          if (ans.compare("UNDETERMINED") == 0 ){
            ans = dbs[i].name;
          }
          else{
            ans = "UNDETERMINED";
            break;
          }
        }
      }
      cout << ans << "\n";
    }
    if (j < cases - 1){
      cout << "\n";
    }
  }
}
