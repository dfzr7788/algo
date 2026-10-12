#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<long long> a(n);
    for (auto &x : a) cin>>x;
    vector<long long> values=a;
    sort(values.begin(),values.end());
    values.erase(unique(values.begin(),values.end()),values.end());
    for (long long x : a)
        cout<<lower_bound(values.begin(),values.end(),x)-values.begin()<<'\n';
}
