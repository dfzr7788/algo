#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; long long goal; cin >> n >> goal;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;
    long long lo=0, hi=*min_element(a.begin(),a.end())*goal;
    auto check = [&](long long t) {
        long long made=0;
        for (long long v : a) {
            long long add=t/v;
            if (add>=goal-made) return true; // 达标即停，避免累计溢出。
            made+=add;
        }
        return false;
    };
    while (lo<hi) {
        long long mid=lo+(hi-lo)/2;
        if (check(mid)) hi=mid;
        else lo=mid+1;
    }
    cout << lo << '\n';
}
