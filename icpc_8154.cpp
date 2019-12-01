#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n ;
    while(cin >> n) {
        long long a[6] = {0};
        for (int i = 1; i <= 2 * n; i++) {
            int m;
            cin >> m;
            if (i <= n) {
                a[i % 3] += m;
            } else {
                a[i % 3 + 3] += m;
            }
        }
        long long res[3] = {0};
        for (int i = 0; i < 3; i++) {
            for (int j = 3; j < 6; j++) {
                res[(i + j) % 3] += (a[i] * a[j]);
            }
        }
        printf("%ld %ld %ld\n", res[1], res[2], res[0]);
    }
    return 0;
}