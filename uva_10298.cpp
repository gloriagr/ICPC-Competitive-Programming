#include <iostream>
#include <vector>

using namespace std;

typedef vector<long long> vi;

string KMP_str; // The string to search in
string KMP_pat; // The pattern to search
vi lps;

// KMP Init
void KMP_init(){
    long long m = KMP_pat.length();
    lps.resize(m,0);
    lps[0] = -1;
    long long i = 0, j = -1;
    while (i < m) {
        while (j >= 0 && KMP_pat[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        lps[i] = j;
    }
}

// Search a pattern in a string
// Assuming lps is allready initialized with KMP_init
long long KMP_search() {
    long long ans = 0;
    long long n = KMP_str.length();
    long long m = KMP_pat.length();
    long long i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        if (j == m) { // Pattern found
            // cout << "The pattern is found at index " << i-j << endl;
            ans++;
            j = lps[j];
        }
    }
    return ans;
}

int main() {
    string input;
    getline(cin, input);

    while (input.compare(".") != 0){
        long long i = 0;
        KMP_str = input + input;
        KMP_pat = input;
        KMP_init();
        i = KMP_search();
        cout << i - 1 << endl;
        getline(cin, input);
    }

    return 0;
}