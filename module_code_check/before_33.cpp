#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long K; cin>>n>>K;
    unordered_map<long long,long long> count;
    long long ans=0;
    for (int i=0; i<n; ++i) {
        long long x; cin>>x;
        auto it=count.find(K-x);
        if (it!=count.end()) ans+=it->second;
        ++count[x];
    }
    cout<<ans<<'\n';
}
