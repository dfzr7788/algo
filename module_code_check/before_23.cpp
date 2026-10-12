#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<long double> a(n);
    for (auto &v : a) cin >> v;
    long double l=*min_element(a.begin(),a.end());
    long double r=*max_element(a.begin(),a.end());
    auto f = [&](long double x) {
        long double sum=0;
        for (long double v : a) { long double d=x-v; sum+=d*d; }
        return sum;
    };
    for (int it=0; it<150; ++it) {
        long double m1=l+(r-l)/3, m2=r-(r-l)/3;
        long double v1=f(m1), v2=f(m2);
        if (v1>v2) l=m1;
        else if (v1<v2) r=m2;
        else { l=m1; r=m2; }
    }
    long double x=(l+r)/2;
    cout << fixed << setprecision(10) << x << ' ' << f(x) << '\n';
}
