#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<vector<long long>> d(n+2,vector<long long>(n+2));
    while (q--) {
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        ++d[x1][y1]; --d[x2+1][y1]; --d[x1][y2+1]; ++d[x2+1][y2+1];
    }
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            d[i][j]+=d[i-1][j]+d[i][j-1]-d[i-1][j-1];
            cout<<d[i][j]<<(j==n?'\n':' ');
        }
    }
}
