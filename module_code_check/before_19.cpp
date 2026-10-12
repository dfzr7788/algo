#include <bits/stdc++.h>
using namespace std;
struct Item { long long w,v; };
vector<Item> a;
long long best=0;
long long upper(int i, long long cap) {
    long long result=0;
    for (; i<(int)a.size(); ++i) {
        if (a[i].w<=cap) { cap-=a[i].w; result+=a[i].v; }
        else {
            result+=(a[i].v*cap+a[i].w-1)/a[i].w;
            break;
        }
    }
    return result;
}
void dfs(int i, long long cap, long long value) {
    best=max(best,value);
    if (i==(int)a.size() || value+upper(i,cap)<=best) return;
    if (a[i].w<=cap) dfs(i+1,cap-a[i].w,value+a[i].v);
    dfs(i+1,cap,value);
}
int main() {
    int n; long long W; cin >> n >> W;
    a.resize(n);
    for (auto &x : a) cin >> x.w >> x.v;
    sort(a.begin(),a.end(),[](const Item &x,const Item &y) {
        return x.v*y.w > y.v*x.w;
    });
    dfs(0,W,0); cout << best << '\n';
}
