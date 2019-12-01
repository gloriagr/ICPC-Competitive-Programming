#include <cmath>
#include <utility>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <functional>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

int closest(vector<int> fibo, int num){
  int current = 0;
  ll fibo_size = fibo.size() - 1;
  while(true){
    if (fibo_size > current && fibo[current + 1] <= num){
      current++;
    }
    else{
      break;
    }
  }
  return current;
}

int main(){
  //init
  vector<int> fibo;
  int prev = 1;
  int next = 2;
  fibo.push_back(prev);
  while(next <= pow(10,9)){
    fibo.push_back(next);
    int tmp = next;
    next += prev;
    prev = tmp;
  }

  int t;
  cin >> t;
  for (int i = 0; i < t; i++){
    int num;
    cin >> num;
    int idx = closest(fibo, num);
    vector<int> ans(idx + 1,0);
    ans[idx] = 1;
    num -= fibo[idx];
    while (num > 0){
      idx = closest(fibo, num);
      ans[idx] = 1;
      num -= fibo[idx];
    }
    for (int j = ans.size() - 1; j >= 0; j--){
      cout << ans[j];
    }
    cout << "\n";
  }
}
