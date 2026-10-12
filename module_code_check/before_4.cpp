#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;
    unordered_map<long long, int> freq;
    int l = 0, best = 0;
    for (int r = 0; r < n; ++r) {
        ++freq[a[r]];
        while (freq[a[r]] > 1) --freq[a[l++]];
        best = max(best, r - l + 1);
    }
    cout << best << '\n';
}
