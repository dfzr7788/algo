#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    long long x; cin>>x;
    long long ending=x,best=x;
    for (int i=1; i<n; ++i) {
        cin>>x; ending=max(x,ending+x); best=max(best,ending);
    }
    cout<<best<<'\n';
}
