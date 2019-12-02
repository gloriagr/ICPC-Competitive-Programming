/* PARADIGM - Greedy */

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
      ll num_boxes;
      ll num_citizens;
      ll rate;
      Node(ll num_boxes1, ll num_citizens1){
        num_boxes = num_boxes1;
        num_citizens = num_citizens1;
        rate = num_citizens / num_boxes;
        
        if (num_citizens % num_boxes > 0) rate++;
      }
};

struct comparator{
    bool operator()(const Node& left, const Node& right){
        return (left.rate < right.rate);
    }
};

int main(){
  while(true) {
    priority_queue<Node,vector<Node>,comparator> max_heap; //T, container, comparator
    ll N,B; 
    cin >> N >> B;
    if (N == -1){
      break;
    }

    ll total = 0;
    ll citizens[N];
    for (int i = 0; i < N; i++){
      cin >> citizens[i];
      total += citizens[i];
    }

    ll spent_boxes = 0;
    for (int i = 0; i < N; i++){
      ll boxes = ((B-N) * citizens[i]) / total;
      boxes++;
      max_heap.push(Node(boxes, citizens[i]));
      spent_boxes += boxes;
    }

    for (int i = spent_boxes; i < B; i++){
      Node tmp = max_heap.top();
      max_heap.pop();
      max_heap.push(Node(tmp.num_boxes + 1, tmp.num_citizens));
    }
    cout << min_heap.top().rate << "\n";
  }

}
