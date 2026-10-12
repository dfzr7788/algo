#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<pair<long long,long long>> a(n);
    for (auto &[l,r] : a) cin>>l>>r;
    sort(a.begin(),a.end());
    long long total=0,l=0,r=0;
    bool active=false;
    for (auto [x,y] : a) {
        if (!active) { l=x; r=y; active=true; }
        else if (x<=r) r=max(r,y);
        else { total+=r-l; l=x; r=y; }
    }
    if (active) total+=r-l;
    cout<<total<<'\n';
}
