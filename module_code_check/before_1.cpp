#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, t; cin >> n >> t;
    vector<int> a(n), next(n);
    for (auto &x : a) cin >> x;
    for (int step = 0; step < t; ++step) {
        for (int i = 0; i < n; ++i)
            next[i] = a[i] ^ a[(i + n - 1) % n];
        a.swap(next);
    }
    for (int i = 0; i < n; ++i)
        cout << a[i] << (i+1 == n ? '\n' : ' ');
}
