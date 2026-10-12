#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    int B=max(1,(int)sqrt(n)),blocks=(n+B-1)/B;
    vector<long long> raw(n),tag(blocks),sum(blocks);
    for (int i=0; i<n; ++i) { cin>>raw[i]; sum[i/B]+=raw[i]; }
    while (q--) {
        int type,l,r; cin>>type>>l>>r; --l; --r;
        long long c=0,ans=0;
        if (type==1) cin>>c;
        for (int i=l; i<=r;) {
            int b=i/B,end=min(n,(b+1)*B);
            if (i==b*B && end-1<=r) {
                if (type==1) { tag[b]+=c; sum[b]+=c*(end-i); }
                else ans+=sum[b];
                i=end;
            } else {
                if (type==1) { raw[i]+=c; sum[b]+=c; }
                else ans+=raw[i]+tag[b];
                ++i;
            }
        }
        if (type==2) cout<<ans<<'\n';
    }
}
