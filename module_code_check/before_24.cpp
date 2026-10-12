#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; long long x; cin >> n >> x;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;
    int l=0;
    long long sum=0, ans=0;
    for (int r=0; r<n; ++r) {
        sum+=a[r];
        while (l<=r && sum>x) sum-=a[l++];
        if (l<=r && sum==x) ++ans;
    }
    cout << ans << '\n';
}
