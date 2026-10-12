#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<long long> d(n+2);
    long long prev=0;
    for (int i=1; i<=n; ++i) { long long x; cin>>x; d[i]=x-prev; prev=x; }
    while (q--) { int l,r; long long c; cin>>l>>r>>c; d[l]+=c; d[r+1]-=c; }
    long long current=0;
    for (int i=1; i<=n; ++i) { current+=d[i]; cout<<current<<(i==n?'\n':' '); }
}
