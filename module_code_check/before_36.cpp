#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<int> lg(n+1);
    for (int i=2; i<=n; ++i) lg[i]=lg[i/2]+1;
    int levels=lg[n]+1;
    vector<vector<long long>> st(levels,vector<long long>(n));
    for (auto &x : st[0]) cin>>x;
    for (int k=1; k<levels; ++k)
        for (int i=0; i+(1<<k)<=n; ++i)
            st[k][i]=max(st[k-1][i],st[k-1][i+(1<<(k-1))]);
    while (q--) {
        int l,r; cin>>l>>r; --l; --r;
        int k=lg[r-l+1];
        cout<<max(st[k][l],st[k][r-(1<<k)+1])<<'\n';
    }
}
