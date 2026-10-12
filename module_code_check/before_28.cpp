#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m,q; cin>>n>>m>>q;
    vector<vector<long long>> s(n+1,vector<long long>(m+1));
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
        long long x; cin>>x;
        s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+x;
    }
    while (q--) {
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        cout<<s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1]<<'\n';
    }
}
