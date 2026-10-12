#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> a(n), pos(n+1);
    for (int i=0; i<n; ++i) { cin >> a[i]; pos[a[i]]=i; }
    vector<pair<int,int>> ops;
    for (int i=0; i<n; ++i) {
        if (a[i]==i+1) continue;
        int j=pos[i+1], other=a[i];
        swap(a[i],a[j]);
        pos[i+1]=i; pos[other]=j;
        ops.push_back({i+1,j+1});
    }
    cout << ops.size() << '\n';
    for (auto [i,j] : ops) cout << i << ' ' << j << '\n';
}
