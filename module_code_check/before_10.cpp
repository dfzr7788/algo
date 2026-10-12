#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<pair<long long,long long>> a(n);
    for (auto &[l,r] : a) cin >> l >> r;
    sort(a.begin(),a.end(),[](auto a, auto b) {
        return a.second < b.second;
    });
    bool selected=false;
    long long last=0;
    int ans=0;
    for (auto [l,r] : a) if (!selected || l>=last) {
        ++ans; last=r; selected=true;
    }
    cout << ans << '\n';
}
