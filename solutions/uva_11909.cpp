#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <chrono>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <fstream>
#include <stack>
#include <algorithm>
using namespace std;

typedef long long ll;



#define EPS 1e-9
#define MAX_SIZE 100

using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))


int main() {
    int l, w, h, t;
    while (cin >> l >> w >> h >> t){
      double alpha = double(h) / double(l);
      double a = tan ( double(t) * PI / 180.0 ) * l;
      if (a <= alpha*l){
        double s1 = a*l/2;
        double s2 = l*h;
        double s3 = s2 - s1;
        double v = s3 * w;
        printf("%.3f mL\n", v);
      }
      else{
        a = tan ( double(90-t) * PI / 180.0 );
        double s = a*double(h)*double(h)/2.0;
        double v = s * w;
        printf("%.3f mL\n", v);
      }

    }
    return 0;
}
