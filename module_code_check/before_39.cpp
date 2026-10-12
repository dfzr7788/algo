#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<vector<long long>> a(n,vector<long long>(n));
    for (auto &row : a) for (auto &x : row) cin>>x;
    long long best=LLONG_MIN;
    for (int top=0; top<n; ++top) {
        vector<long long> col(n);
        for (int bottom=top; bottom<n; ++bottom) {
            for (int j=0; j<n; ++j) col[j]+=a[bottom][j];
            long long ending=col[0]; best=max(best,ending);
            for (int j=1; j<n; ++j) {
                ending=max(col[j],ending+col[j]); best=max(best,ending);
            }
        }
    }
    cout<<best<<'\n';
}
