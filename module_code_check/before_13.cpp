#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    if (n == 2 || n == 3) { cout << "NO SOLUTION\n"; return 0; }
    vector<int> ans;
    for (int x = 2; x <= n; x += 2) ans.push_back(x);
    for (int x = 1; x <= n; x += 2) ans.push_back(x);
    for (int i = 0; i < n; ++i) cout << ans[i] << (i+1==n ? '\n' : ' ');
}
