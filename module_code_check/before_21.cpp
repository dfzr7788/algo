#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> a(n), count(n+1);
    for (int &x : a) { cin >> x; ++count[x]; }
    long long total=0;
    for (long long c : count) total += c*(c-1)/2;
    for (int x : a) cout << total-(count[x]-1) << '\n';
}
