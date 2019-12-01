#include <iostream>
#include <vector>
#include <ctime>
#include <stdio.h>

typedef long long ll;

using namespace std;

ll calc_gcd(ll a, ll b){
    if(a == 0) return b;
    if(b == 0) return a;
    if(b > a)
        return calc_gcd(b,a);
    else
        return calc_gcd(b, a % b);
}

int main(){
    ll cases;
    scanf("%lld\n",&cases);
    for (ll t = 0; t < cases; t++){
        ll eqs;
        cin >> eqs;
        ll result = 0;
        ll max_a10 = 1;
        for (ll i = 0; i < eqs; i++) {
            ll sum = 0;
            ll tmp;
            for (ll l = 0; l < 9; l++) {
                cin >> tmp;
                sum += tmp;
            }
            cin >> tmp;
            if(max_a10 < tmp) 
                max_a10 = tmp;
            if (tmp > sum)
                result = -1;
            if (result >= 0) {
                sum -= tmp;
                result = calc_gcd(sum, result); //
            }
        }
        if(result < 2 || result <= max_a10) {
            printf("impossible\n");
        } else {
            cout << result << "\n";
        }
    }
  return 0;
}