#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    long long total = 0;
    for (auto &x : a) { cin >> x; total += x; }
    long long best = total;
    for (unsigned mask = 0; mask < (1u << n); ++mask) {
        long long sum = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1u << i)) sum += a[i];
        // 避免先计算 2*sum；两组和均非负且不超过 total。
        best = min(best, llabs(sum - (total - sum)));
    }
    cout << best << '\n';
}
