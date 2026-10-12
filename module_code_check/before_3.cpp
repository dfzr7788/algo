#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    long long target;
    cin >> n >> target;
    vector<pair<long long, int>> a(n);
    for (int i = 0; i < n; ++i) { cin >> a[i].first; a[i].second = i + 1; }
    sort(a.begin(), a.end());
    int l = 0, r = n - 1;
    while (l < r) {
        long long s = a[l].first + a[r].first;
        if (s == target) {
            cout << a[l].second << ' ' << a[r].second << '\n';
            return 0;
        }
        if (s < target) ++l;
        else --r;
    }
    cout << "IMPOSSIBLE\n";
}
