#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,q; cin >> n >> q;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;
    vector<pair<long long,int>> queries(q);
    for (int i=0; i<q; ++i) { cin >> queries[i].first; queries[i].second=i; }
    sort(a.begin(),a.end());
    sort(queries.begin(),queries.end());
    vector<int> ans(q);
    int p=0;
    for (auto [x,id] : queries) {
        while (p<n && a[p]<=x) ++p;
        ans[id]=p;
    }
    for (int x : ans) cout << x << '\n';
}
