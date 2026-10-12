#include <bits/stdc++.h>
using namespace std;
struct Op { int l,r; long long d; };
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m,k; cin>>n>>m>>k;
    vector<long long> a(n+1),times(m+2),delta(n+2);
    for (int i=1; i<=n; ++i) cin>>a[i];
    vector<Op> ops(m+1);
    for (int i=1; i<=m; ++i) cin>>ops[i].l>>ops[i].r>>ops[i].d;
    while (k--) { int x,y; cin>>x>>y; ++times[x]; --times[y+1]; }
    for (int i=1; i<=m; ++i) {
        times[i]+=times[i-1];
        long long value=times[i]*ops[i].d;
        delta[ops[i].l]+=value; delta[ops[i].r+1]-=value;
    }
    for (int i=1; i<=n; ++i) {
        delta[i]+=delta[i-1];
        cout<<a[i]+delta[i]<<(i==n?'\n':' ');
    }
}
