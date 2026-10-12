#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    long long lo = 0, hi = 0;
    for (auto &x : a) { cin >> x; lo = max(lo, x); hi += x; }
    auto check = [&](long long limit) {
        int parts = 1;
        long long sum = 0;
        for (long long x : a) {
            if (x > limit) return false;
            if (sum > limit - x) { ++parts; sum = x; }
            else sum += x;
        }
        return parts <= k;
    };
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << '\n';
}
