#include <bits/stdc++.h>
using namespace std;
vector<long long> a, tmp;
long long solve(int l, int r) {
    if (r - l <= 1) return 0;
    int m = l + (r - l) / 2;
    long long ans = solve(l, m) + solve(m, r);
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else {
            ans += m - i;
            tmp[k++] = a[j++];
        }
    }
    while (i < m) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int p = l; p < r; ++p) a[p] = tmp[p];
    return ans;
}
int main() {
    int n;
    cin >> n;
    a.resize(n); tmp.resize(n);
    for (auto &x : a) cin >> x;
    cout << solve(0, n) << '\n';
}
