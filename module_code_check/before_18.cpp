#include <bits/stdc++.h>
using namespace std;
vector<long long> sums(const vector<long long> &a) {
    vector<long long> s{0};
    s.reserve(size_t(1) << a.size());
    for (long long x : a) {
        size_t old = s.size();
        for (size_t i=0; i<old; ++i) s.push_back(s[i]+x);
    }
    return s;
}
int main() {
    int n; long long x; cin >> n >> x;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;
    int m=n/2;
    vector<long long> left=sums(vector<long long>(a.begin(),a.begin()+m));
    vector<long long> right=sums(vector<long long>(a.begin()+m,a.end()));
    sort(right.begin(),right.end());
    long long ans=0;
    for (long long s : left) {
        auto range=equal_range(right.begin(),right.end(),x-s);
        ans+=range.second-range.first;
    }
    cout << ans << '\n';
}
